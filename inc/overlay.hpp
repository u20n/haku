#pragma once
#include <atomic>
#include <deque>

#include "../widgets/history.hpp"

struct mqueue {
  std::atomic<bool> newm{false};
  std::deque<std::string> queue;
  void notify() {
    this->newm = !newm;
    this->newm.notify_all();
    this->newm = !newm;
  }
};

// pure virtual template for overlays
struct overlay {
  mqueue* mq;
  virtual void display(history* h) = 0;
  overlay(mqueue* mq) : mq(mq) {}
};
