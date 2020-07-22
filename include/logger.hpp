#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "sinks/basic_file_sink.h"
#include "sinks/stdout_color_sinks.h"
#include "spdlog.h"


namespace muser::logger {
    extern std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink;
    extern std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink;
    extern std::shared_ptr<spdlog::logger> logger;
    // create logger with 2 targets with different log levels and formats.
    // the console will show only warnings or errors, while the file will log all.
    void init_logger();
}  // namespace muser::logger

#endif