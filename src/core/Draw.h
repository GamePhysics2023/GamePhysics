#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct ImColor;

namespace Draw {
// Draw a line from the start to the end point.
void line(const glm::vec2& start, const glm::vec2& end);
// Draw a circle.
void circle(const glm::vec2& center, float radius, bool filled = false);
// Draw an axis aligned rectangle.
void aabb(const glm::vec2& min, const glm::vec2& max, bool filled = false);

// Set the color to draw with.
void setColor(ImColor color);
// Set the thickness to draw with.
void setThickness(float thickness);
// Reset color and thickness.
void reset();

// Begin drawing a frame. Called from Simple2DScene.
void begin();
// Finish drawing a frame. Called from Simple2DScene.
void end();
// Set the camera matrix. Called from Simple2DScene.
void setCamera(const glm::mat4& vpMatrix);
// Setup the viewport in the current ImGui window. Called from Simple2DScene.
void setupImGuiViewport();
// Set the viewport. Called from Simple2DScene.
void setViewport(float x, float y, float width, float height);
// Convert vector from screen space to world space.
glm::vec2 vectorScreenToGame(glm::vec2 vector);
} // namespace Draw

namespace Input {
// Returns the mouse position in world coordinates.
glm::vec2 getMousePos();
// Returns the mouse position in imgui window coordinates.
glm::vec2 getMousePosInWindow();
} // namespace Input