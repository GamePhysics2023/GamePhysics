#pragma once

#include "core/Simple2DScene.h"
#include <vector>
#include "objects/Circle.h"

class FireworksScene : public Simple2DScene {
public:
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void drawGUI() override;

    virtual const char* getName() override { return "Fireworks"; }

private:
    std::vector<Circle> circles;
    glm::vec2 gravity = glm::vec2(0, -9.81f);

    int numberOfCircles = 10;
    float radius = 2;
    float velocityMultiplier = 1;
    float circleRadius = 1;
};