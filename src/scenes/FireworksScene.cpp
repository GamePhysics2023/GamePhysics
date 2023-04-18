#include "FireworksScene.h"

#include "imgui.h"

void FireworksScene::onEnable() {
	circles.push_back(Circle(glm::vec2(0, 0), glm::vec2(0, 0), gravity, 1, 1));
    circles.push_back(Circle(glm::vec2(3, 0), glm::vec2(0, 0), gravity, .5f, .5f));
}

void FireworksScene::onDisable() {}

void FireworksScene::update(float deltaTime) {
    for (auto& circle : circles) {
        circle.update(deltaTime);
    }
}

void FireworksScene::draw() {
    for (auto& circle : circles) {
        circle.draw();
    }
}

void FireworksScene::drawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}
