
#include "g3log/logworker.hpp"
#include "g3log/sinkhandle.hpp"
#include "g3sinks/syslogsink.hpp"

#pragma once

namespace g3 {
static const int kErrorValue = 700;
static const int kAppFatalValue = 900;
}  // namespace g3

const LEVELS ERROR{g3::kErrorValue, {"ERROR"}}, APPFATAL{g3::kAppFatalValue, {"FATAL"}};  // Subsystem fatal error

namespace toylab {
namespace log {

class ToylabLog {
  public:
    ToylabLog();
    ~ToylabLog();

  private:
    std::unique_ptr<g3::LogWorker> logworker;
    std::unique_ptr<g3::SinkHandle<g3::SyslogSink>> sink_handle;
};

}  // namespace log
}  // namespace toylab

#include "g3log/g3log.hpp"
