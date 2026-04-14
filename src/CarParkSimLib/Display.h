#pragma once

#include <string>

class Display {

public:
  Display(const std::string &displayName);
  Display() = delete;

  void showMessage(const std::string &message) const;

private:
  std::string displayName_;
};
