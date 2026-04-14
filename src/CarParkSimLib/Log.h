#pragma once

#include <format>
#include <iostream>
#include <string>

void inline log4(const std::string &entity, const std::string &message,
                 const std::string &regMark, const std::string &ticket) {
  std::cout << std::format("[{}] {} - {} ({})\n", entity, message, regMark,
                           ticket);
}

void inline log3(const std::string &entity, const std::string &message,
                 const std::string &regMark) {
  std::cout << std::format("[{}] {} - {}\n", entity, message, regMark);
}

void inline log2(const std::string &entity, const std::string &message) {
  std::cout << std::format("[{}] {}\n", entity, message);
}
