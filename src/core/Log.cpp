#include "core/Log.h"
#include "spdlog/common.h"
#include "spdlog/logger.h"

#include <memory>
#include <vector>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ringbuffer_sink.h>

namespace dc8 {
    namespace {
        std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> memSink;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> conSink;
    }

    void log::init() {
        conSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        conSink->set_pattern("[%H:%M:%S.%e] [%^%L%$] %v");
        conSink->set_level(spdlog::level::trace);

        memSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(2000);
        memSink->set_pattern("[%H:%M:%S.%e] [%L] %v");
        memSink->set_level(spdlog::level::trace);

        std::vector<spdlog::sink_ptr> sinks {
            conSink,
            memSink
        };

        auto logger = std::make_shared<spdlog::logger>("emu", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::warn);

        spdlog::set_default_logger(logger);
    }

    bool log::hasLogLevel(spdlog::level::level_enum level) {
        return spdlog::default_logger()->level() == level;
    }

    void log::setLogLevel(spdlog::level::level_enum level) {
        spdlog::default_logger()->set_level(level);
    }

    std::vector<std::string> log::getMessages() {
        if (!memSink) {
            return {};
        }

        return memSink->last_formatted();
    }
}
