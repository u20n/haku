#pragma once

#include "../inc/widget.hpp"
#include "inputl.hpp"
#include "history.hpp"

struct focus : public widget {
  history* h; inputl* l;
  
  void bump(int char_code) override {
   

  }

  focus (
    history* h_,
    inputl* l_
  ) : h(h_), l(l_) {

  }
};
