#pragma once

#include "ANPRReading.h"
#include "Car.h"
#include "log.h"
#include <random>
#include <string>

class ANPRCamera {
public:
  ANPRCamera(double reliability);

  ANPRCamera() = delete;

  ANPRReading readRegistrationMark(const Car &car);

private:
  std::bernoulli_distribution dist_;
  std::mt19937 rng_{std::random_device{}()};
};
