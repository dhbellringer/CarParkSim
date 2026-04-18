#pragma once

#include <string>

enum class ANPRResult {
  Success
  , Failure
};

struct ANPRReading {
  ANPRResult Result;
  std::string RegistrationMark;
};