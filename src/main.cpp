#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/FireworksScene.h"

int main(int argc, char** argv) {
    std::vector<Scene*> scenes = {
        new TestScene(), new FireworksScene()
    };
    Application app(scenes);
    //app.showDemoWindow(true);
    return app.run();
}
