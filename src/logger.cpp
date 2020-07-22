#include "logger.hpp"

namespace muser::logger {
    decltype(console_sink) console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    decltype(file_sink) file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/muser.txt", true);
    decltype(logger) logger = std::make_shared<spdlog::logger>("main", spdlog::sinks_init_list{console_sink, file_sink});
    // create logger with 2 targets with different log levels and formats.
    // the console will show only warnings or errors, while the file will log all.
    void init_logger() {
        console_sink->set_level(spdlog::level::warn);
        console_sink->set_pattern("[%H:%M:%S] %^%-7!l%$: %v");
        file_sink->set_level(spdlog::level::trace);
        logger->set_level(spdlog::level::debug);
        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
        spdlog::set_error_handler([](const std::string &msg) { spdlog::get("main")->error("*** LOGGER ERROR ***: {}", msg); });
    }
}  // namespace muser::logger
