#include "log.hpp"


namespace Log {

//time [log_type] file func line message
#define LOG_MSG "%s: [%s] %s %s:%d -> %s\n"

  LoggerConfig default_config = {.file = true, .func = true, .line = true, .time = true};
  Logger::Logger() {
    log_type = LOGGER_STDERR;
    fd = -1;
    file_name = NULL;
    config = default_config;

  }
  Logger::~Logger() {
    if (this->log_type == LOGGER_FILE || this->log_type == LOGGER_SOCKET) {
      close(this->fd);
    }
    if (this->file_name != null) {
      delete [] this->file_name;
    }
  }

  Logger default_logger;

  void setLoggerConfig(LoggerConfig conf, LoggerType type, ...) {
    default_config = conf;
    default_logger.log_type = type;
    if (type == LOGGER_FILE) {
      va_list li;
      va_start(li, type);

      char *file_name = va_arg(li, char *);
      i32 file_name_len = strlen(file_name);
      default_logger.file_name = new char [file_name_len + 1];
      strcpy(default_logger.file_name, file_name);

    }
  }

  static char *prepareMessage(LoggerLevel level, const char *file, const char *func, i32 line, char *msg) {
    Strbuf sb;
    if (default_logger.config.time) {
      time_t local_time = time(null);
      struct tm *t = localtime(&local_time);
      char buf[512]{0};
      strftime(buf, 512, "%Y-%m-%d : %H-%M-%S", t);
      sb << (const char *)buf;
      sb << (const char *)" ";
    }
    switch(level) {
      case TRACE: {
        sb << (const char *)"[TRACE] ";
      } break;
      case INFO: {
        sb << (const char *)"[INFO] ";
      } break;
      case DEBUG: {
        sb << (const char *)"[DEBUG] ";
      } break;
      case ERROR: {
        sb << (const char *)"[ERROR] ";
      } break;
      case FATAL: {
        sb << (const char *)"[FATAL] ";
      } break;
    }
    if (default_logger.config.file) {
      sb << (const char *)file;
      sb << (const char *)" ";
    }
    if (default_logger.config.func) {
      sb << (const char *)func;
      sb << (const char *)":";
    }
    if (default_logger.config.line) {
      char buf[32]{0};
      sprintf(buf, "%d", line);
      sb << (const char *)buf;
    }
    sb << (const char *)" -> ";
    sb << (const char *)msg;
    sb << "\n";
    char *res = sb.toString();
    return res;
  }

  void write_level(LoggerLevel level, const char *file, const char *func, int line, const char *fmt, ...) {
    char tmp_buf[1024]{0};
    va_list li;
    va_start(li, fmt);
    vsprintf(tmp_buf, fmt, li);
    char *msg = prepareMessage(level, file, func, line, tmp_buf);
    i32 msg_len = strlen(msg);
    if (default_logger.log_type == LOGGER_STDERR) {
      i32 write_bytes = write(STDERR_FILENO, msg, msg_len);
      if (write_bytes != msg_len) {
        fprintf(stderr, "Logger error while write msg: %s\n", msg);
      }
    } else if (default_logger.log_type == LOGGER_FILE) {
      if (default_logger.fd != -1) {
        i32 write_bytes = write(default_logger.fd, msg, msg_len);
        if (write_bytes != msg_len) {
          fprintf(stderr, "Logger error while write into file msg: %s\n", msg);
        }
      } else {
        i32 fd;
        if (access(default_logger.file_name, F_OK) == 0) {
          fd = open(default_logger.file_name, O_APPEND | O_WRONLY, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
        } else {
          fd = open(default_logger.file_name, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
        }
        if (fd <= 0) {
          fprintf(stderr, "Logger error while open file %s\n", default_logger.file_name);
          return;
        }
        default_logger.fd = fd;
        i32 write_bytes = write(default_logger.fd, msg, msg_len);
        if (write_bytes != msg_len) {
          fprintf(stderr, "Logger error while write into file msg: %s\n", msg);
        }
      }
    } else {
      //TODO(maxim) write this function HTTP HTTPS logger write
    }
    delete [] msg;
  }
}

