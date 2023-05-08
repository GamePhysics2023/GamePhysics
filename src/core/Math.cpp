#include "Math.h"
#include <SDL_stdinc.h>

glm::mat4 Math::modelMatrix2D(const glm::vec2& position, float angle) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix[0][0] = cosf(angle);
    modelMatrix[1][0] = -sinf(angle);
    modelMatrix[0][1] = sinf(angle);
    modelMatrix[1][1] = cosf(angle);
    modelMatrix[3][0] = position.x;
    modelMatrix[3][1] = position.y;
    return modelMatrix;
}

std::vector<glm::vec2> Math::transformPolygon(
    const std::vector<glm::vec2>& points,
    const glm::vec2& position,
    float angle) {
    std::vector<glm::vec2> transformedPoints;
    transformedPoints.reserve(points.size());
    glm::mat4 modelMatrix = Math::modelMatrix2D(position, angle);

    for (const auto& point : points) {
        transformedPoints.push_back(modelMatrix *
                                    glm::vec4(point.x, point.y, 0, 1));
    }

    return transformedPoints;
}

std::vector<glm::vec2> Math::generateRegularPolygon(int pointCount,
                                              float radius) {
    std::vector<glm::vec2> points;
    float pi2 = M_PI * 2;
    for (int i = 0; i < pointCount; i++) {
        float t = (float)i / pointCount;
        points.push_back(
            glm::vec2(cosf(t * pi2) * radius, sinf(t * pi2) * radius));
    }
    return points;
}