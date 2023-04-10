#pragma once

#include <vector>
#include "Scene.h"

#include "imgui.h"

struct SDL_Window;

// Main application class of the program.
class Application {
public:
    Application(const std::vector<Scene*>& scenes);
    ~Application();

    // The main loop of the application.
    int run();

    // Show the Dear ImGui demo window.
    void showDemoWindow(bool show);

private:
    // The main loop of the application.
    void mainLoop(const ImGuiIO& io);
    // Render the menu bar.
    void menuBar();
    // Render the stats window.
    void statsWindow(const ImGuiIO& io);
    // Render the settings window.
    void settingsWindow();
    // Render the control window.
    void controlWindow();

    // All available scenes.
    std::vector<Scene*> scenes;
    // The currently shown scene.
    Scene* currentScene;
    // Show the Dear ImGui demo window.
    bool isDemoWindowVisible = false;
    // Show the stats window.
    bool isStatsWindowVisible = false;
    // Show the settings window.
    bool isSettingsWindowVisible = false;
    // Is the application still running?
    bool isRunning = true;
    // Performance counter value of the previous frame. Used to calculate the
    // delta time.
    uint64_t lastPerformanceCount = 0;

    SDL_Window* window = nullptr;
    bool isPaused = false;
    bool isStepping = false;
    ImVec4 clearColor;

    bool isVsyncEnabled = true;
    bool isFramerateCapped = false;
    float framerateCap = 60;
};