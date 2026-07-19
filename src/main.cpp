#include "Application.h"
#include "core/Log.h"
#include "window/AppWindow.h"
#include <memory>

int main() {
    dc8::log::init();
    dc8::log::info("Dreamy CHIP-8 started.");

    {
        dc8::platform::AppWindow window;
        if (!window.create()) {
            return 1;
        }

        window.setRootEntity(std::make_unique<dc8::Application>());
        window.run();
    }

    dc8::log::shutdown();
    return 0;
}
