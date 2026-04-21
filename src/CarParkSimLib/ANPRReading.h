#pragma once

#include <string>
#include "StrongID.h"

enum class ANPRResult {
  Success
  , Failure
};

struct ANPRReading {
  ANPRResult Result_;
  RegistrationMark RegistrationMark_;
};