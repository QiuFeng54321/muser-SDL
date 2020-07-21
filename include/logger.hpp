#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "sinks/basic_file_sink.h"
#include "sinks/stdout_color_sinks.h"
#include "spdlog.h"


namespace muser::logger {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/muser.txt", true);
    auto logger = spdlog::logger("main", {console_sink, file_sink});
    // create logger with 2 targets with different log levels and formats.
    // the console will show only warnings or errors, while the file will log all.
    void init_logger() {
        console_sink->set_level(spdlog::level::warn);
        console_sink->set_pattern("[%H:%M:%S] %^%-7!l%$: %v");
        file_sink->set_level(spdlog::level::trace);
        logger.set_level(spdlog::level::debug);
    }
}  // namespace muser::logger

#endif