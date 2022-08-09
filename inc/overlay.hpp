#pragma once
#include <atomic>
#include <deque>

struct mqueue {
  std::atomic<bool> newm{false};
  std::deque<std::string> queue;
  void notify() {
    this->newm = !newm;
    this->newm.notify_all();
    this->newm = !newm;
  }
};



// pure virual extension for the overlay
struct overlay {
  mqueue* mq;

  overlay(mqueue* mq) : mq(mq) {}
};
