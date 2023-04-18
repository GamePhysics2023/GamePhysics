#include "Circle.h"

#include "core/Draw.h"

Circle::Circle(const glm::vec2& position,
               const glm::vec2& velocity,
               const glm::vec2& acceleration,
               float radius,
               float mass)
    : position(position),
velocity(velocity), acceleration(acceleration), radius(radius) {
    if (mass == 0) {
        inverseMass = 0;
    } else {
        inverseMass = 1.f / mass;
    }
}

void Circle::draw() {
    Draw::circle(position, radius);
}

void Circle::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}
