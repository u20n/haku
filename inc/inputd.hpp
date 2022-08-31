#pragma once
#include <map>
#include <unordered_set>
#include <utility>
#include "widget.hpp"

#include "../config.h"

// input daemon
// first widget provided is considered the root
// widget, that will be given focus after 
// an escape event
using escape_tuple = std::tuple<
  widget*,
  std::vector<int>,
  unsigned int
>;
using escape_type = std::vector<escape_tuple>;

struct inputd {  
public:
  escape_type escape;
  escape_type::iterator focused;
  
  void cycle(int char_code) {
    if (char_code == KEY_RESIZE) {
      // this needs to be broadcast
      for (const auto& [w, s, i]: this->escape) {
        w->bump(char_code);
      }
    }

    std::get<0>(*this->focused)->bump(char_code);
    auto& index = std::get<2>(*this->focused);
    auto& sequence = std::get<1>(*this->focused);
    if (sequence.at(index) == char_code) {
      if (index+1 == sequence.size()) {
        // reset
        index = 0;
        // escape
        focus((unsigned int) 0);
      } else {
        index++;
      }
    }
  } 
  
  void focus(widget* w) {
    for (unsigned int i=0; i<escape.size(); i++) {
      if (std::get<0>(escape.at(i)) == w) {
        focus(i);
      }
    }
  }
  void focus(unsigned int i) {focused = (escape.begin() + i);}

  inputd(std::vector<std::tuple<widget*, std::vector<int>>> temp) {
    for (const auto& e: temp) {
      const auto& w = std::get<0>(e); const auto& s = std::get<1>(e);
      escape.push_back(escape_tuple(w, s, 0));
    }
  }
};
