#pragma once

#include "splash.hpp"
#include <thread>

/**
 * looped splash screen
 * extends functionality of
 * normal splash
 * */
struct lsplash {
  std::vector<splash> frames; 
  std::atomic<bool> stop = false;
  unsigned int interval = 300;

  void play() { 
    unsigned int i=0;
    while(!stop) {
      if (i<this->frames.size()) {
        clear();
        this->frames.at(i).show();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
        i++;
      }
      i = 0;
    }
  }

  void halt() {
    this->stop = true;
    this->stop.notify_all(); // redundant
  }

  lsplash(std::vector<std::vector<std::string>> f) {
    for (auto frame : f) {
      this->frames.push_back(splash{frame});
    }
  }
};
