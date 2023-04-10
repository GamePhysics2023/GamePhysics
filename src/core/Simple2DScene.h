#pragma once

#include <glm/glm.hpp>
#include "core/Scene.h"

// Scene class that sets up an orthographic 2D camera and allows using the
// simple draw functions in the Draw namespace.
class Simple2DScene : public Scene {
public:
    Simple2DScene();
    ~Simple2DScene();

    virtual void render() override;

    // Use the simple draw functions from the Draw namespace to draw in this function.
    virtual void draw() = 0;
    // Draw additional ImGui windows.
    virtual void drawGUI() = 0;

private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 matrix;
    glm::mat4 identity;

    glm::vec2 cameraCenter;
    float orthographicSize;

    bool isCameraWindowVisible;
    bool isMovingCamera;
    glm::vec2 lastMousePos = glm::vec2(0);
};
