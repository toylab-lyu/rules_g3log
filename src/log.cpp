#include "toylab/log.hpp"

#include <iostream>
#include <mutex>

#include <unistd.h>
#include <limits.h>
#include <syslog.h>

namespace toylab {
namespace log {

namespace internal {

static inline std::string WhoAmI() {
    char realpath[PATH_MAX] = {0};
    auto nbytes = readlink("/proc/self/exe", realpath, sizeof(realpath));
    if (nbytes == -1) {
        std::cerr << "readlink for /proc/self/exe error." << std::endl;
        return "Unknown";
    }

    std::string exec_name{realpath};
    size_t pos = exec_name.rfind('/');
    if (pos != std::string::npos) {
        exec_name.erase(exec_name.begin(), exec_name.begin() + pos + 1);
    }

    return exec_name;
}

std::string &ModuleName() {
    static std::string module_name;
    static std::once_flag name_unitialized_flag;
    std::call_once(name_unitialized_flag, []() { module_name = WhoAmI(); });

    return module_name;
}

/*
 * std::strftime()
 *   %F          Equivalent to %Y-%m-%d (the ISO 8601 date format)
 *   %T          The time in 24-hour notation (%H:%M:%S).
 * g3::internal::localtime_formatted_fractions()
 *   %f3:        milliseconds, 3 digits: 001
 *   %f6:        microseconds, 6 digits: 000001
 *   %f, %f9     nanoseconds, 9 digits: 000000001
 */
static const std::string toylab_log_time_formatted = "%F %T.%f9";  // "%Y/%m/%d %H:%M:%S.000000001"

std::string GetFormattedLog(const g3::LogMessage &msg) {
    static std::stringstream ss;
    ss.str("");
    ss << "<" << msg.timestamp(toylab_log_time_formatted) << ">"
       << "[" << msg.level() << " " << msg.file() << ":" << msg.function() << ":" << msg.line() << "] ";
    return ss.str();
}

const std::map<int, int> g_autel_log_level = {{G3LOG_DEBUG.value, LOG_DEBUG},
                                              {INFO.value, LOG_INFO},
                                              {WARNING.value, LOG_WARNING},
                                              {ERROR.value, LOG_ERR},
                                              {APPFATAL.value, LOG_CRIT},
                                              {FATAL.value, LOG_CRIT}};

std::unique_ptr<g3::SyslogSink> ToylabSyslogSink(const std::string &module_name = ModuleName()) {
    auto sink = std::make_unique<g3::SyslogSink>(module_name.c_str());
    sink->setFormatter(&GetFormattedLog);
    sink->setLevelMap(g_autel_log_level);
    sink->echoToStderr();
    return sink;
}

}  // namespace internal

ToylabLog::ToylabLog() {
    g3::only_change_at_initialization::addLogLevel(ERROR);
    g3::only_change_at_initialization::addLogLevel(APPFATAL);

    logworker = g3::LogWorker::createLogWorker();
    sink_handle = logworker->addSink(internal::ToylabSyslogSink(), &g3::SyslogSink::syslog);
    g3::initializeLogging(logworker.get());
}

ToylabLog::~ToylabLog() {
    g3::internal::shutDownLogging();
}

static ToylabLog _g_toylab_log{};

}  // namespace log
}  // namespace toylab
