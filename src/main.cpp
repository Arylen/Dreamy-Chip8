#include "core/Log.h"
#include "window/AppWindow.h"

int main() {
    dc8::log::init();
    dc8::log::info("Dreamy CHIP-8 started.");

    {
        dc8::platform::AppWindow appWindow;
        if (!appWindow.create()) {
            return 1;
        } else {
            appWindow.run();
        }
    }

    dc8::log::shutdown();
    return 0;
}
