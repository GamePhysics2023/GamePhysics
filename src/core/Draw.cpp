#include "Draw.h"

// Directly convert from imgui vectors to glm vectors.

#define IM_VEC2_CLASS_EXTRA                            \
    constexpr ImVec2(glm::vec2& f) : x(f.x), y(f.y) {} \
    operator glm::vec2() const { return glm::vec2(x, y); }

#define IM_VEC4_CLASS_EXTRA                                                  \
    constexpr ImVec4(const glm::vec4& f) : x(f.x), y(f.y), z(f.z), w(f.w) {} \
    operator glm::vec4() const { return glm::vec4(x, y, z, w); }

#include <iostream>
#include "imgui.h"

namespace Draw {

ImDrawList* drawList;
glm::mat4 camMatrix;
glm::mat4 camMatrixInv;

struct Context {
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    ImColor color = ImColor(255, 255, 255, 255);
    float thickness = 1.0f;
};

Context gContext;

void begin() {
    drawList = ImGui::GetWindowDrawList();
}

void end() {
    reset();
}

void setViewport(float x, float y, float width, float height) {
    gContext.x = x;
    gContext.y = y;
    gContext.width = width;
    gContext.height = height;
}

void setCamera(const glm::mat4& vpMatrix) {
    camMatrix = vpMatrix;
    camMatrixInv = glm::inverse(vpMatrix);
}

ImVec2 transformPoint(const glm::mat4& mat, const glm::vec2& p) {
    glm::vec4 trans(p, 0, 1);
    trans = mat * trans;
    trans *= 0.5f / trans.w;
    trans += glm::vec4(0.5f, 0.5f, 0, 0);
    trans.y = 1.f - trans.y;
    trans.x *= gContext.width;
    trans.y *= gContext.height;
    trans.x += gContext.x;
    trans.y += gContext.y;
    return ImVec2(trans.x, trans.y);
}

float transformLength(const glm::mat4& mat, float l) {
    return mat[0][0] * 0.5f * l * gContext.width;
}

void line(const glm::vec2& p1, const glm::vec2& p2) {
    ImVec2 p1l = transformPoint(camMatrix, p1);
    ImVec2 p2l = transformPoint(camMatrix, p2);
    drawList->AddLine(p1l, p2l, gContext.color, gContext.thickness);
}

void setupImGuiViewport() {
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    auto viewportX = viewportMinRegion.x + viewportOffset.x;
    auto viewportY = viewportMinRegion.y + viewportOffset.y;
    auto viewportWidth = viewportMaxRegion.x - viewportMinRegion.x;
    auto viewportHeight = viewportMaxRegion.y - viewportMinRegion.y;
    Draw::setViewport(viewportX, viewportY, viewportWidth, viewportHeight);
}

void circle(const glm::vec2& center, float radius, bool filled) {
    ImVec2 centerl = transformPoint(camMatrix, center);
    float radiusl = transformLength(camMatrix, radius);

    if (radiusl > 1e10 || radiusl < 0) {
        return;
    }
    if (filled) {
        drawList->AddCircleFilled(centerl, radiusl, gContext.color, 0);
    } else {
        drawList->AddCircle(centerl, radiusl, gContext.color, 0,
                            gContext.thickness);
    }
}

void aabb(const glm::vec2& min, const glm::vec2& max, bool filled) {
    ImVec2 minl = transformPoint(camMatrix, min);
    ImVec2 maxl = transformPoint(camMatrix, max);

    if (filled) {
        drawList->AddRectFilled(minl, maxl, gContext.color, 0, 0);
    } else {
        drawList->AddRect(minl, maxl, gContext.color, 0, 0, gContext.thickness);
    }
}

void setColor(ImColor color) {
    gContext.color = color;
}

void setThickness(float thickness) {
    gContext.thickness = thickness;
}

void reset() {
    gContext.color = 0xffffffff;
    gContext.thickness = 1;
}

glm::vec2 vectorScreenToGame(glm::vec2 vector) {
    return vector / glm::vec2(camMatrix[0][0], camMatrix[1][1]);
}

} // namespace Draw

namespace Input {

glm::vec2 getMousePos() {
    glm::vec2 mouse = ImGui::GetMousePos();

    mouse.x -= Draw::gContext.x;
    mouse.y -= Draw::gContext.y;
    mouse.x /= Draw::gContext.width;
    mouse.y /= Draw::gContext.height;
    mouse.y = 1.f - mouse.y;
    mouse.x -= 0.5f;
    mouse.y -= 0.5f;
    mouse /= 0.5f;
    glm::vec4 position = glm::vec4(mouse, 0, 1);
    position = Draw::camMatrixInv * position;

    return position;
}

glm::vec2 getMousePosInWindow() {
    glm::vec2 mouse = ImGui::GetMousePos();

    mouse.x -= Draw::gContext.x;
    mouse.y -= Draw::gContext.y;
    mouse.x /= Draw::gContext.width;
    mouse.y /= Draw::gContext.height;
    mouse.y = 1.f - mouse.y;
    mouse.x -= 0.5f;
    mouse.y -= 0.5f;
    mouse /= 0.5f;
    return mouse;
}
} // namespace Input