#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <atomic>
#include <cmath>

#include "../base.hpp"
#include "../screen.hpp"

struct splash {
  std::vector<std::string> img;
  /** 
   * while sound in principle, this is pretty annoying to use in practice; 
   * TODO: come up with a better solution
   * */
  std::atomic<bool>* ready;  

  void show(int y=-1, int x=-1) { // defaults to center if y,x < 0
    unsigned int my, mx;
    getmaxyx(stdscr, my, mx);

    /**
     * generate approriate center (assuming equal length strings)
     * the process is almost identical between x and y
     * */
    if (y < 0 || x < 0) {
      unsigned int ix = img.at(0).size(); 
      x = floor((mx-ix)/2);
      unsigned int iy = img.size();
      y = floor((my-iy)/2);
    }
    // print splash
    for (unsigned int i=0; i<my; i++) {
      if (i < (unsigned int) y || i+1 > (img.size()+y)) { // y offsets
        printl(i, newl());
      } else {
        printl(i, lmargin(x, img.at(i-y)));
      } 
    }
    // block until ready
    ready->wait(false);
  }
  
  splash(
      std::vector<std::string> img,
      std::atomic<bool>* ready
    ) : img(img), ready(ready) {}
};
