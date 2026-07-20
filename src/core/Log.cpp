#include "core/Log.h"

#include <memory>
#include <vector>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ringbuffer_sink.h>

namespace dc8 {
    namespace {
        std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> memSink;
    }

    void log::init() {
        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console->set_pattern("[%H:%M:%S.%e] [%^%L%$] %v");
        console->set_level(spdlog::level::debug);

        memSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(2000);
        memSink->set_pattern("[%H:%M:%S.%e] [%L] %v");
        memSink->set_level(spdlog::level::debug);

        std::vector<spdlog::sink_ptr> sinks {
            console,
            memSink
        };

        auto logger = std::make_shared<spdlog::logger>("emu", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::warn);

        spdlog::set_default_logger(logger);
    }

    std::vector<std::string> log::getMessages() {
        if (!memSink) {
            return {};
        }

        return memSink->last_formatted();
    }
}
