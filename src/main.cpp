#include "core/Log.h"
#include <thread>

int main() {
    Log::init();

    for (int i = 0; i < 1000; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Log::info("Info?");
    }

    Log::shutdown();
    return 0;
}
