#ifndef CPPLIB_IO_LOG_HPP
#define CPPLIB_IO_LOG_HPP

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "../core/strbuf.hpp"


namespace Log {

#define trace(...) write_level(Log::TRACE, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define info(...) write_level(Log::INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define debug(...) write_level(Log::DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define error(...) write_level(Log::ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define fatal(...) write_level(Log::FATAL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

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
  //if  @type == LOGGER_FILE, set in args file_name
  void setLoggerConfig(LoggerConfig conf, LoggerType type, ...);
}

#endif //CPPLIB_IO_LOG_HPP
