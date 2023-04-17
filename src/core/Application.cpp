#include "Application.h"

#include <SDL.h>
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include "ImGuizmo.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "core/Draw.h"
#include "imgui.h"
#include "Preferences.h"

Application::Application(const std::vector<Scene*>& scenes)
    : scenes(scenes), clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)) {
    currentScene = *scenes.rbegin();
}

Application::~Application() {
    scenes.clear();
}

int Application::run() {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    if (currentScene == nullptr) {
        printf("Error: No scene supplied.");
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                          SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Game Physics", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Regular.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Regular.ttf", 32.0f);

    // Load Preferences
    Preferences::load();
    isStatsWindowVisible = Preferences::getBool("stats_window");
    isSettingsWindowVisible = Preferences::getBool("settings_window");
    isVsyncEnabled = Preferences::getBool("vsync");
    isFramerateCapped = Preferences::getBool("framerate_capped");
    framerateCap = Preferences::getFloat("framerate_cap", 60.0f);

    SDL_GL_SetSwapInterval(isVsyncEnabled); // Enable vsync

    // Initialize first scene.
    currentScene->onEnable();

    mainLoop(io);

    Preferences::save();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Application::showDemoWindow(bool show) {
    isDemoWindowVisible = true;
}

void Application::mainLoop(const ImGuiIO& io) {
    lastPerformanceCount = SDL_GetPerformanceCounter();
    float totalTime = 0;

    while (isRunning) {
        Uint64 frameStart = SDL_GetPerformanceCounter();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                isRunning = false;
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window))
                isRunning = false;
        }

        // Calculate delta time.
        Uint64 performanceCount = SDL_GetPerformanceCounter();
        float deltaTime = (float)(performanceCount - lastPerformanceCount) /
                          SDL_GetPerformanceFrequency();
        lastPerformanceCount = performanceCount;

        // Start the Dear ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        ImGui::DockSpaceOverViewport();

        menuBar();

        // Windows
        if (isDemoWindowVisible) {
            ImGui::ShowDemoWindow(&isDemoWindowVisible);
        }
        statsWindow(io);
        controlWindow();
        settingsWindow();

        // Show the current scene.
        if (!isPaused || isStepping) {
            totalTime += deltaTime;
            currentScene->update(deltaTime);
        }

        currentScene->render();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w,
                     clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        isStepping = false;

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);

        if (isFramerateCapped) {
            float elapsedMs =
                (float)(SDL_GetPerformanceCounter() - frameStart) /
                SDL_GetPerformanceFrequency() * 1000.0f;
            int sleep =
                std::max(0.0f, floor(1000.0f / framerateCap - elapsedMs));
            SDL_Delay(sleep);
        }
    }
}

void Application::menuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit", "Cmd+Q")) {
                isRunning = false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scenes")) {
            for (const auto& scene : scenes) {
                if (ImGui::MenuItem(scene->getName(), nullptr,
                                    currentScene == scene)) {
                    std::cout << "Switch to scene " << scene->getName() << "."
                              << std::endl;
                    // Switch scene
                    if (currentScene) {
                        currentScene->onDisable();
                    }
                    currentScene = scene;
                    if (currentScene) {
                        currentScene->onEnable();
                    }
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::MenuItem("Stats", nullptr, isStatsWindowVisible)) {
                isStatsWindowVisible = !isStatsWindowVisible;
                Preferences::setBool("stats_window", isStatsWindowVisible);
                Preferences::save();
            }
            if (ImGui::MenuItem("Settings", nullptr, isSettingsWindowVisible)) {
                isSettingsWindowVisible = !isSettingsWindowVisible;
                Preferences::setBool("settings_window", isSettingsWindowVisible);
                Preferences::save();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Application::statsWindow(const ImGuiIO& io) {
    if (isStatsWindowVisible) {
        ImGui::Begin("Stats", &isStatsWindowVisible);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}

void Application::settingsWindow() {
    if (isSettingsWindowVisible) {
        ImGui::Begin("Settings", &isSettingsWindowVisible);
        if (ImGui::Checkbox("Enable VSync", &isVsyncEnabled)) {
            SDL_GL_SetSwapInterval(isVsyncEnabled);
            Preferences::setBool("vsync", isVsyncEnabled);
            Preferences::save();
        }

        if (ImGui::Checkbox("Cap Framerate", &isFramerateCapped)) {
            Preferences::setBool("cap_framerate", isFramerateCapped);
            Preferences::save();
        }
        ImGui::SameLine();
        if (ImGui::DragFloat("##Framerate Cap", &framerateCap, 1.f, 1, 0,
                             "%.1f")) {
            Preferences::setFloat("framerate_cap", framerateCap);
        }
        ImGui::End();
    }
}

void Application::controlWindow() {
    ImGui::Begin("Control");
    if (isPaused) {
        if (ImGui::Button("Play", {50, 22})) {
            isPaused = false;
        }
    } else {
        if (ImGui::Button("Pause", {50, 22})) {
            isPaused = true;
        }
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!isPaused);
    if (ImGui::Button("Step")) {
        isStepping = true;
    }
    ImGui::EndDisabled();
    ImGui::End();
}
