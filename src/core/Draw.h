#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct ImColor;

namespace Draw {
// Draws a line from the start to the end point.
void line(const glm::vec2& start, const glm::vec2& end);
// Draws an arrow from the start to the end point.
void arrow(const glm::vec2& start, const glm::vec2& end, float headThickness = 0.02f);
// Draws a circle.
void circle(const glm::vec2& center, float radius, bool filled = false);
// Draws an axis aligned rectangle.
void aabb(const glm::vec2& min, const glm::vec2& max, bool filled = false);
// Draws a polygon.
void polygon(const glm::vec2 position,
             const glm::vec2* points,
             int pointCount,
             bool filled = false);
void polygon(const glm::mat4& modelMatrix,
             const glm::vec2* points,
             int pointCount,
             bool filled = false);
// Draws a polyline.
void polyline(const glm::vec2 position,
              const glm::vec2* points,
              int pointCount);
void polyline(const glm::mat4& modelMatrix,
              const glm::vec2* points,
              int pointCount);
// Draws a rectangle.
void rect(const glm::vec2& position,
          float angle,
          const glm::vec2& halfExtends,
          bool filled = false);
void rect(const glm::mat4& modelMatrix,
          const glm::vec2& halfExtends,
          bool filled = false);
// Draws a grid.
void grid(const glm::vec2& min,
          const glm::vec2& max,
          const glm::vec2& lineDistance);
// Draws some text.
void text(const glm::vec2& position, const char* text);

// Sets the color to draw with.
void setColor(ImColor color);
// Sets the thickness to draw with.
void setThickness(float thickness);
// Resets color and thickness.
void reset();

// Draws a handle that the user can use to modify the position.
void positionHandle(glm::vec2& position);
void positionHandle(glm::mat4& modelMatrix);
// Draws a handle that the user can use to modify the rotation.
void rotationHandle(glm::mat4& modelMatrix);

// Begins drawing a frame. Called from Simple2DScene.
void begin();
// Finishs drawing a frame. Called from Simple2DScene.
void end();
// Sets the camera matrix. Called from Simple2DScene.
void setCamera(const glm::mat4& vpMatrix);
// Sets the viewport up in the current ImGui window. Called from Simple2DScene.
void setupImGuiViewport();
// Sets the viewport. Called from Simple2DScene.
void setViewport(float x, float y, float width, float height);
// Converts vector from screen space to world space.
glm::vec2 vectorScreenToGame(glm::vec2 vector);
} // namespace Draw

namespace Input {
// Returns the mouse position in world coordinates.
glm::vec2 getMousePos();
// Returns the mouse position in imgui window coordinates.
glm::vec2 getMousePosInWindow();
// Returns true if the mouse button is currently pressed.
bool isMouseDown(int mouseButton);
// Returns true if the mouse button was pressed this frame.
bool isMouseClicked(int mouseButton);
// Returns true if the mouse button was released this frame.
bool isMouseReleased(int mouseButton);
} // namespace Input