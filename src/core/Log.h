#pragma once

#include "spdlog/spdlog.h"

namespace dc8::log {
    void init();

    using spdlog::trace;
    using spdlog::debug;
    using spdlog::info;
    using spdlog::warn;
    using spdlog::error;
    using spdlog::critical;

    using spdlog::shutdown;
}
