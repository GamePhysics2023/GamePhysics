#include "Math.h"

glm::mat4 Math::modelMatrix2D(const glm::vec2& position, float rotation) {
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix[0][0] = cosf(rotation);
    modelMatrix[1][0] = -sinf(rotation);
    modelMatrix[0][1] = sinf(rotation);
    modelMatrix[1][1] = cosf(rotation);
    modelMatrix[3][0] = position.x;
    modelMatrix[3][1] = position.y;
    return modelMatrix;
}