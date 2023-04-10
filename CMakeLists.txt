cmake_minimum_required(VERSION 3.20)

set(NAME "GamePhysics")
project(${NAME})


file(GLOB_RECURSE SCENE_SOURCES CONFIGURE_DEPENDS "src/scenes/**.cpp" "src/scenes/**.h")

add_executable(${NAME} src/main.cpp ${SCENE_SOURCES})
source_group("scenes" FILES ${SCENE_SOURCES})

target_include_directories(${NAME} PRIVATE src)

# Set as the initial startup project.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NAME})

# Enable folders in Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Copy assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Core library
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS "src/core/**.cpp")
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "src/core/**.h")

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(core PUBLIC src)
target_link_libraries(${NAME} core)

# Dependencies
include(FetchContent)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY})

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG efec5db081e3aad807d0731e172ac597f6a39447
)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)
endif ()
target_include_directories(core PUBLIC ${glm_SOURCE_DIR})

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(core SDL2::SDL2 SDL2::SDL2main)

if (WIN32)
  # Copy DLL files on Windows to the target App build folder.
  add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE_DIR:${NAME}>)
endif ()

# Dear ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG 6b3435a2db4d28cb4b71de8ef06b097df2d840f7 # latest commit on docking branch
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
    file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
    add_library(imgui STATIC
        ${IMGUI_SOURCES}
        ${IMGUI_HEADERS}
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    target_link_libraries(imgui ${OPENGL_LIBRARIES} SDL2::SDL2)
    set_target_properties(imgui PROPERTIES FOLDER "Dependencies")
endif ()

target_link_libraries(core imgui)

# ImGuizmo
FetchContent_Declare(
    imguizmo
    GIT_REPOSITORY https://github.com/CedricGuillemet/ImGuizmo.git
    GIT_TAG fbc3614abcc642de7f3868cc0d68a35503ca9a4e
)
if (NOT imguizmo_POPULATED)
    FetchContent_Populate(imguizmo)
    set(imguizmo_INCLUDE_DIR ${imguizmo_SOURCE_DIR}/)
    file(GLOB imguizmo_SOURCES ${imguizmo_SOURCE_DIR}/*.cpp)
    file(GLOB imguizmo_HEADERS ${imguizmo_SOURCE_DIR}/*.h)
    add_library(imguizmo STATIC
        ${imguizmo_SOURCES}
        ${imguizmo_HEADERS}
    )

    target_include_directories(imguizmo PUBLIC ${imguizmo_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    target_link_libraries(imguizmo imgui)
    set_target_properties(imguizmo PROPERTIES FOLDER "Dependencies")
endif ()

target_link_libraries(core imguizmo)
