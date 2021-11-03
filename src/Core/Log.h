#pragma once

#include "Core/Core.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

// Core log macros
#define SC_TRACE(...) Log::GetLogger()->trace(__VA_ARGS__)
#define SC_INFO(...)  Log::GetLogger()->info(__VA_ARGS__)
#define SC_WARN(...)  Log::GetLogger()->warn(__VA_ARGS__)
#define SC_ERROR(...) Log::GetLogger()->error(__VA_ARGS__)
#define SC_FATAL(...) Log::GetLogger()->fatal(__VA_ARGS__)

class Log {
 public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger>& GetLogger() {
    return s_Logger;
  }

 private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};
