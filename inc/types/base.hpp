#pragma once
#include <fstream>
#include <string>

namespace base {
  template<typename... T>
  void log(
      std::string lf, // log file
      T... t // assorted error message
  ) {
    std::fstream f(lf);
    while (f.is_open()) {
      ((f << t), ...);
    }
  }
};

