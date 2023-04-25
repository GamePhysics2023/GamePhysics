#include "HalfspaceCollisionScene.h"

#include "imgui.h"
#include "core/Draw.h"
#include "core/Colors.h"


void HalfspaceCollisionScene::onEnable() {}

void HalfspaceCollisionScene::onDisable() {}

void HalfspaceCollisionScene::update(float deltaTime) {}

void HalfspaceCollisionScene::draw() {
    Draw::positionHandle(circle.position);

    bool isColliding = false;

    float projectedDistance = glm::dot(circle.position, halfspace.normal);

    Draw::setColor(Colors::blue);
    Draw::arrow(glm::vec2(0), halfspace.normal);


    float distance = projectedDistance - circle.radius;
    //Draw::arrow(circle.position, circle.position - halfspace.normal * projectedDistance);
    isColliding = distance < 0;


    Draw::setColor(isColliding ? Colors::red : Colors::white);

    halfspace.draw();
    circle.draw();
}

void HalfspaceCollisionScene::drawGUI() {
    ImGui::Begin("Inspector");

    if (ImGui::DragFloat2("Halfspace", &halfspace.dir[0], 0.2f)) {
        halfspace.normal =
            glm::normalize(glm::vec2(-halfspace.dir.y, halfspace.dir.x));
    }
    ImGui::End();
}
