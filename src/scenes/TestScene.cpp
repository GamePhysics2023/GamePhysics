#include "TestScene.h"

#include "core/Draw.h"
#include "imgui.h"

TestScene::TestScene() : circlePosition(0, 1), circleRadius(1) {}

TestScene::~TestScene() {}

void TestScene::onEnable() {}

void TestScene::onDisable() {}

void TestScene::update(float deltaTime) {
    circleVelocity += circleAcceleration * deltaTime;
    circlePosition += circleVelocity * deltaTime;

    if (circlePosition.y - circleRadius < groundY) {
        circlePosition.y = groundY + circleRadius;
        circleVelocity.y *= -1;
    }

}

void TestScene::draw() {
    Draw::circle(circlePosition, circleRadius);
    Draw::line(glm::vec2(-5, 0), glm::vec2(5, 0));
}

void TestScene::drawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat2("Circle Velocity", &circleVelocity[0], 0.1f);
    ImGui::DragFloat2("Circle Acceleration", &circleAcceleration[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);



    if (ImGui::Button("Reset")) {
        circleVelocity = glm::vec2(0);
        circleAcceleration = glm::vec2(0, -9.81);
    }

    ImGui::End();

}