#include "core/Log.h"

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void Log::init() {
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    console->set_pattern("[%H:%M:%S.%e] [%^%L%$] %v");
    console->set_level(spdlog::level::debug);

    auto logger = std::make_shared<spdlog::logger>("emu", console);
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::warn);

    spdlog::set_default_logger(logger);
}
