#pragma once

#include <glm/glm.hpp>

class Circle {
public:
    Circle(const glm::vec2& position,
           const glm::vec2& velocity,
           const glm::vec2 & acceleration,
           float radius,
           float mass);

    void draw();
    void update(float deltaTime);

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;

    float radius;
    float inverseMass;

};