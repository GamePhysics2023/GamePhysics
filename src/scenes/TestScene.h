#pragma once

#include <glm/glm.hpp>
#include "core/Simple2DScene.h"
#include "objects/Test.h"

class TestScene : public Simple2DScene {
public:
    TestScene();
    ~TestScene();

    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void drawGUI() override;

    virtual const char* getName() override { return "Test Scene"; }

private:
    glm::vec2 circlePosition;
    glm::vec2 circleVelocity = glm::vec2(0);
    glm::vec2 circleAcceleration = glm::vec2(0, -9.81f);
    float circleRadius;
    float groundY = 0;
};