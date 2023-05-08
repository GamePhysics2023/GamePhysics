#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Math {

glm::mat4 modelMatrix2D(const glm::vec2& position, float angle);

// Transforms the points of a polygon to world space.
std::vector<glm::vec2> transformPolygon(const std::vector<glm::vec2>& points,
                                        const glm::vec2& position,
                                        float angle);

// Generates the points for a regular polygon in counter-clockwise order.
std::vector<glm::vec2> generateRegularPolygon(int pointCount, float radius = 1);

}