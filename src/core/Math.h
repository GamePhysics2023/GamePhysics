#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Math {

// Calculates the 4x4 matrix for the given position and angle.
glm::mat4 modelMatrix2D(const glm::vec2& position, float angle);

// Transforms the points of a polygon to world space.
std::vector<glm::vec2> transformPolygon(const std::vector<glm::vec2>& points,
                                        const glm::vec2& position,
                                        float angle);

// Generates the points for a regular polygon in counter-clockwise order.
std::vector<glm::vec2> generateRegularPolygon(int pointCount, float radius = 1);

// Calculates the z component of the cross product (a.x, a.y, 0) x (b.x, b.y, 0).
float crossProduct2D(const glm::vec2& a, const glm::vec2& b);

// Generates the points for a rectangle and transforms them to world space.
std::vector<glm::vec2> getRectangleWorldPoints(const glm::vec2& position,
                                               float angle,
                                               const glm::vec2& halfExtends);

} // namespace Math