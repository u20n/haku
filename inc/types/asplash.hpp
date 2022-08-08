#pragma once

#include "splash.hpp"
#include <thread>

/**
 * animated splash screen
 * extends functionality of
 * normal splash
 * */
struct asplash {
  std::vector<splash> frames;
  std::vector<std::atomic<bool>> control;
  std::atomic<bool> stop = false;
  unsigned int interval = 300;

  void play() { // play one cycle of the animation 
    for (unsigned int i=0; i<this->frames.size(); i++) {
      std::jthread tmp{&splash::show, &(this->frames.at(i))};
      tmp.detach();
      std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
      this->control.at(i) = false;
      this->control.at(i).notify_all();
      this->control.at(i) = true; // flip it back (splash's design is kind of jank here)
      i++;
    }
    this->stop = true;
  }

  void halt() {
    this->stop = true;
    this->stop.notify_all(); // redundant
  }

  asplash(std::vector<std::vector<std::string>> f) {
    for (auto frame : f) {
      std::atomic<bool> c{false};
      this->frames.push_back(splash{frame, &c});
      this->control.push_back(c);
    }
  }
};
