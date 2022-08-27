#pragma once
#include <map>
#include <unordered_set>

#include "widget.hpp"

// input daemon
using emap = std::map<
  widget*,  
  std::unordered_set<int> // key codes
>;
struct inputd {
  emap escape_map {};
  
  emap::iterator focused, root;

  bool escaped = false;

  void cycle(int char_code) {
    if (char_code == KEY_RESIZE) {
      // this needs to be broadcast
      for (const auto& [w, kc]: this->escape_map) {
        w->bump(char_code);
      }
    }

    if (this->escaped) {
      // choose widget? (this seems like the job of another widget)
      return;
    }

    for (const auto k: this->focused->second) {
      if (k == char_code) {
        // escape, return
        this->escaped = true;
        // input daemon needs some way of signalling
        // that it's escaped
        // both to the other widgets
        // and to the user
        return;
      }
    }
    this->focused->first->bump(char_code);
  }

  void set_escape(widget* w, std::unordered_set<int> kc) {
    this->escape_map[w] = kc;
  }
  
  void set_focused(widget* w) {
    this->focused = this->escape_map.find(w);
    // TODO, QoL add auto add if not found
  }
  
  // EARLY, root widget to control, well, which widget is focused
  // this root widget CANNOT have any escape characters
  void set_root(widget* w) {
    this->root = this->escape_map.find(w);
  }

  inputd(emap&& temp_map) {
    escape_map = temp_map;
  }

  inputd(std::initializer_list<widget*> W) {
    for (const auto& w: W) {
      this->escape_map.insert({w, {}});
    }
  }
};