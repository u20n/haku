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
    curs_set(0); // hide cursor
    unsigned int i=0;
    while(!this->stop) {
      if (i<this->frames.size()) { // this completes the frame loop, even if we're supposed to be closed
        clear();
        this->frames.at(i).show();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
        i++;
      } else {
        i = 0;
      }
    }
    curs_set(1); // show cursor
  }

  void halt() {
    this->stop = true;
    this->stop.notify_all(); // for observing entities
    clear();
  }

  lsplash(std::vector<std::vector<std::string>> f) {
    for (auto frame : f) {
      this->frames.push_back(splash{frame});
    }
  }
};