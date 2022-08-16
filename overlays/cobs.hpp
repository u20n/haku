#pragma once

#include "../inc/push.hpp"
#include <graph.hpp>
#include <nhlomann/json.hpp>

struct cobs {
private:
  std::unordered_set<std::string> p_trips;
  std::string trip;
public:
  std::unordered_set<std::string> p_trips() {
    return this->p_trips;
  }
  std::string trip() {
    return this->trip;
  }
  std::string parse(std::string fpath) {    
    std::string f = bfs::read(fpath);
    /** actually parse it */
    json j{j};
    
  }
};
