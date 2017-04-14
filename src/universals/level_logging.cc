#ifdef LEVEL_LOGGING
#include <iomanip>
#endif
#include <ostream>
#include <stdexcept>
#include <string>

#ifdef LEVEL_LOGGING
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/detail/light_rw_mutex.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/keywords/file_name.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/rotation_size.hpp>
#include <boost/log/keywords/start_thread.hpp>
#include <boost/log/keywords/time_based_rotation.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/shared_ptr.hpp>
#endif

#include "escape.h"
#include "level_logging.h"

namespace universals {
using namespace std;
#ifdef LEVEL_LOGGING
using namespace boost::log;
#endif

log_level
parse_log_level(const string& level) {
  if (level == "fatal")
    return log_level::fatal;
  if (level == "error")
    return log_level::error;
  if (level == "warn")
    return log_level::warning;
  if (level == "info")
    return log_level::info;
  if (level == "debug")
    return log_level::debug;
  if (level == "trace")
    return log_level::trace;
  throw invalid_argument{"invalid log level"};
}

using file_sink = sinks::synchronous_sink<sinks::text_file_backend>;

void
init_file_collecting(const char* logs_dir, boost::shared_ptr<file_sink> sink) {
  sink->locked_backend()->set_file_collector(sinks::file::make_collector(keywords::target = logs_dir, keywords::max_size = 16 * 1024 * 1024, keywords::min_free_space = 100 * 1024 * 1024));
}

void
init_logging(const char* logs_dir, log_level level) {
#ifdef LEVEL_LOGGING
  int severity = trivial::info;
  switch (level) {
  case log_level::fatal:
    severity = trivial::fatal;
    break;
  case log_level::error:
    severity = trivial::error;
    break;
  case log_level::warning:
    severity = trivial::warning;
    break;
  case log_level::info:
    severity = trivial::info;
    break;
  case log_level::debug:
    severity = trivial::debug;
    break;
  case log_level::trace:
    severity = trivial::trace;
    break;
  }
  if (logs_dir) {
    add_common_attributes();

    boost::shared_ptr<file_sink> sink(new file_sink(keywords::file_name = "%Y%m%d_%H%M%S_%5N.log", keywords::rotation_size = 10 * 1024 * 1024, keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), keywords::auto_flush = true));

    // Set up where the rotated files will be stored
    init_file_collecting(logs_dir, sink);

    // Upon restart, scan the directory for files matching the file_name pattern
    sink->locked_backend()->scan_for_files();

    sink->set_formatter(expressions::stream << expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << ": [" << setw(7) << trivial::severity << "] " << expressions::smessage);
    // Add the sink to the core
    core::get()->add_sink(sink);
    core::get()->set_filter(trivial::severity >= severity);
  } else
    core::get()->set_logging_enabled(false);
#else
  throw runtime_error{"file logging not supported!"};
#endif
}

void
log_fatal(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(fatal) << msg;
#endif
}

void
log_error(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(error) << msg;
#endif
}

void
log_warning(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(warning) << msg;
#endif
}

void
log_info(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(info) << msg;
#endif
}

void
log_debug(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(debug) << msg;
#endif
}

void
log_trace(const string& msg) {
#ifdef LEVEL_LOGGING
  BOOST_LOG_TRIVIAL(trace) << msg;
#endif
}

void
log_fatal_tee(ostream& os, const string& msg) {
  log_fatal(msg);
  os << msg << endl;
}

void
log_error_tee(ostream& os, const string& msg) {
  log_error(msg);
  os << msg << endl;
}

void
log_warning_tee(ostream& os, const string& msg) {
  log_warning(msg);
  os << msg << endl;
}

void
log_info_tee(ostream& os, const string& msg) {
  log_info(msg);
  os << msg << endl;
}

void
log_debug_tee(ostream& os, const string& msg) {
  log_debug(msg);
  os << msg << endl;
}

void
log_trace_tee(ostream& os, const string& msg) {
  os << msg << endl;
}

void
log_info_start(int argc, const char* argv[]) {
  vector<const char*> args;
  for (auto i = 0; i < argc; ++i)
    args.push_back(argv[i]);
  log_info("starting: " + escape(args));
}
}
