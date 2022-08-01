#pragma once
#include "base.hpp"

/** 
 * does all of the server abstraction work for the user 
 * */
struct agent {
  /** this is really *attempt* to parse */
  virtual void parse(std::string m) = 0;
  /** essentially extended push */
  virtual void send(std::string m) = 0;
};

