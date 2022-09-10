#pragma once
#include "history.hpp"

struct inputl {
protected:
  history* h;
  std::string mbuff, cmd_buff;
  bool cmd_active = false;
  
  void cmd_parse();
public:
  unsigned int cindex, actual, mode;
  void bump(int c);
  void push(int c);
  void show();
  
  inputl(history* h) : h(h) {}
};
