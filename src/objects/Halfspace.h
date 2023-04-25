#pragma once

#include <glm/glm.hpp>
class Halfspace {
public:
    Halfspace(const glm::vec2& dir);

    void draw();

    glm::vec2 dir;
    glm::vec2 normal;
};