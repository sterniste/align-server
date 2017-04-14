#pragma once

#include <iosfwd>
#include <string>

namespace universals {

enum class log_level { fatal = -3, error = -2, warning = -1, info = 0, debug = 1, trace = 2 };

log_level parse_log_level(const std::string& level);
void init_logging(const char* logs_dir, log_level level = log_level::info);

void log_fatal(const std::string& msg);
void log_error(const std::string& msg);
void log_warning(const std::string& msg);
void log_info(const std::string& msg);
void log_debug(const std::string& msg);
void log_trace(const std::string& msg);

void log_fatal_tee(std::ostream& os, const std::string& msg);
void log_error_tee(std::ostream& os, const std::string& msg);
void log_warning_tee(std::ostream& os, const std::string& msg);
void log_info_tee(std::ostream& os, const std::string& msg);
void log_debug_tee(std::ostream& os, const std::string& msg);
void log_trace_tee(std::ostream& os, const std::string& msg);

void log_info_start(int argc, const char* argv[]);
}
