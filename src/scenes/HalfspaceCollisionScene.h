#pragma once

#include <vector>
#include "core/Simple2DScene.h"
#include "objects/Halfspace.h"
#include "objects/Circle.h"

class HalfspaceCollisionScene : public Simple2DScene {
public:
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void drawGUI() override;

    virtual const char* getName() override { return "Halfspace Collision"; };

private:
    Circle circle = Circle(glm::vec2(0, 2), glm::vec2(0), glm::vec2(0), 1, 1);
    Halfspace halfspace = Halfspace(glm::vec2(1, 1));
};
