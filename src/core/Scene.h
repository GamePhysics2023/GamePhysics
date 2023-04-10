#pragma once

// Interface for a scene that can be shown in the application.
struct Scene {
public:
    // Called when this scene is activated.
    virtual void onEnable() = 0;
    // Called when this scene is deactivated.
    virtual void onDisable() = 0;
    // Update the scene every frame.
    virtual void update(float deltaTime) = 0;
    // Render the scene every frame.
    virtual void render() = 0;
    // Return the display name of the scene.
    virtual const char* getName() = 0;
};