#pragma once

#include <ranges>
#include <string>
#include <ncurses.h>
#include <vector>

#include "screen.hpp"

struct history {
protected:
  unsigned int YMOD = 0; // y modifier, e.g. scroll distance 
  std::vector<std::string> layers;
  void bump(std::string); // this is just an interface for the incoming UNIX socket
public:
  void show();
};
