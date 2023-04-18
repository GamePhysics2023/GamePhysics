#include "FireworksScene.h"

#include "imgui.h"
#include "core/Draw.h"
#include "SDL_stdinc.h"

void FireworksScene::onEnable() {
	circles.push_back(Circle(glm::vec2(0, 0), glm::vec2(0, 0), gravity, 1, 1));
    circles.push_back(Circle(glm::vec2(3, 0), glm::vec2(0, 0), gravity, .5f, .5f));
}

void FireworksScene::onDisable() {}

void FireworksScene::update(float deltaTime) {
    for (auto& circle : circles) {
        circle.update(deltaTime);
    }

    if (Input::isMouseClicked(0)) {
        glm::vec2 position = Input::getMousePos();



        for (int i = 0; i < numberOfCircles; i++) {
            float angle = (2 * M_PI) / numberOfCircles * i;
            glm::vec2 dir = glm::vec2(cosf(angle), sinf(angle));
            circles.push_back(
            Circle(position + dir * radius, dir * velocityMultiplier, gravity, circleRadius, 1));

        }

    }

}

void FireworksScene::draw() {
    for (auto& circle : circles) {
        circle.draw();
    }
}

void FireworksScene::drawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragInt("Number of circles", &numberOfCircles);
    ImGui::DragFloat("Spawn Radius", &radius, 0.1f);
    ImGui::DragFloat("Speed", &velocityMultiplier, 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::End();
}
