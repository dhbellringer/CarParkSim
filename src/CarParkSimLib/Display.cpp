
#include <iostream>
#include <format>
#include "Display.h"

Display::Display(const std::string &displayName)
    : displayName_(displayName) {}


void Display::showMessage(const std::string &message) const {
  std::cout << std::format("{}: {}\n", displayName_,  message);
}

