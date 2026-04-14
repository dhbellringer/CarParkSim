#pragma once

#include <random>
#include "ANPRReading.h"
#include "Car.h"

class ANPRCamera {
public:
  ANPRCamera(double reliability);

  ANPRCamera() = delete;

  ANPRReading readRegistrationMark(const Car &car);

private:
  std::bernoulli_distribution dist_;
  std::mt19937 rng_{std::random_device{}()};
};
