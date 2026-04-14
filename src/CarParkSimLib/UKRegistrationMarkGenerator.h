#pragma once

#include <array>
#include <random>
#include <string>

class UKRegistrationMarkGenerator {
public:
  UKRegistrationMarkGenerator() : rng_(std::random_device{}()) {}

  std::string generate() {
    return randomLetters(2) + randomDigits(2) + " " + randomLetters(3);
  }

private:
  std::mt19937 rng_;

  static constexpr std::array<char, 23> letters_{
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
      'N', 'P', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'
      // Excluding I, O, Q, Z for realism
  };

  std::string randomLetters(std::size_t count) {
    std::uniform_int_distribution<std::size_t> dist(0, letters_.size() - 1);
    std::string s;
    s.reserve(count);
    for (std::size_t i = 0; i < count; ++i)
      s.push_back(letters_[dist(rng_)]);
    return s;
  }

  std::string randomDigits(std::size_t count) {
    std::uniform_int_distribution<int> dist(0, 9);
    std::string s;
    s.reserve(count);
    for (std::size_t i = 0; i < count; ++i)
      s.push_back('0' + dist(rng_));
    return s;
  }
};

