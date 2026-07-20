#include "Application.h"
#include "core/Log.h"
#include "window/AppWindow.h"

int main() {
    dc8::log::init();
    dc8::log::info("Dreamy CHIP-8 started.");

    {
        dc8::Application app;
        dc8::platform::AppWindow window { app };

        if (!window.create()) {
            return 1;
        }

        window.run();
    }

    dc8::log::shutdown();
    return 0;
}
