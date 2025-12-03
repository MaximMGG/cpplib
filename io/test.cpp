#include "log.hpp"


int main() {
  Log::setLoggerConfig((Log::LoggerConfig){.file = true, .func = true, .line = true, .time = true}, Log::LOGGER_FILE, "test_file.log");
  Log::info("sdf");
  Log::debug("This is debug %s test %ld", "III", (long)234234);
  Log::fatal("FATALITY...");

  return 0;
}
