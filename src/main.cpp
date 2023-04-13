#include "core/Application.h"
#include "scenes/TestScene.h"

int main(int argc, char** argv) {
    std::vector<Scene*> scenes = {
        new TestScene(),
    };
    Application app(scenes);
    app.showDemoWindow(true);
    return app.run();
}
