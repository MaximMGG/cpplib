#ifndef CPPLIB_IO_LOG_HPP
#define CPPLIB_IO_LOG_HPP

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "../core/strbuf.hpp"


namespace log {

#define trace(...) write_level(log::TRACE, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define info(...) write_level(log::INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define debug(...) write_level(log::DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define error(...) write_level(log::ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define fatal(...) write_level(log::FATAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

  enum LoggerLevel{
    TRACE, INFO, DEBUG, ERROR, FATAL
  };

  struct LoggerConfig{
    bool file;
    bool func;
    bool line;
    bool time;
  };

  enum LoggerType {
    LOGGER_FILE, LOGGER_STDERR, LOGGER_SOCKET
  };
  struct Logger {
    LoggerType log_type;
    int fd;
    char *file_name;
    LoggerConfig config;
    Logger();
    ~Logger();
  };
  void write_level(LoggerLevel level, const char *file, const char *func, int line, const char *fmt, ...);
  void setLoggerConfig(LoggerConfig conf);
}

#endif //CPPLIB_IO_LOG_HPP
