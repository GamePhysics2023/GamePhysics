#include "Halfspace.h"

#include "core/Draw.h"

Halfspace::Halfspace(const glm::vec2& dir) : dir(dir) {
    normal = glm::normalize(glm::vec2(-dir.y, dir.x));
}

void Halfspace::draw() {
    Draw::line(-dir*5.f, dir*5.f);
}
