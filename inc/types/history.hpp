#pragma once

#include <ranges>
#include <string>
#include <ncurses.h>

#include "../screen.hpp"

struct history {
  unsigned int MARGIN = 20;
  unsigned int YMOD = 0; // y modifier, e.g. scroll distance
   
  void sety(unsigned int y) {YMOD = y;}
  void setm(unsigned int m) {MARGIN = m;}

  std::vector<std::string> layers;

  void add_new(std::string m) {
    unsigned int mx = getmaxx(stdscr);
    unsigned int aspace = mx-(MARGIN*2);

    std::vector<std::string> words;
    if (m.size() > aspace) {
      // split (shamelessly stolen from SO)
      size_t last, next = 0; 
      while ((next = m.find(" ", last)) != std::string::npos) {
        words.push_back(m.substr(last, next-last));
        last = next+1;
      }
      words.push_back(m.substr(last));

      unsigned int i, lindex = 0; // layer index
      while (i<words.size()) {
        if (words.at(i).size() > aspace) { // the word is too big, hypenate
          std::string big = words.at(i);
          std::string half1 = big.substr(0, aspace-1);
          std::string half2 = big.substr(aspace-1, big.size()-half1.size());
          half1.append("-");

          // inject
          words.at(i) = half1;
          words.insert(words.begin()+(i+1), half2); 
          continue; // try again
        }
        if (this->layers.at(lindex).size() + words.at(i).size() > aspace) {
          lindex++; // next layer
        } else {
          this->layers.at(lindex)+=words.at(i);
          i++;
        }
      }
    } else {
      // pad
      while(m.size() < aspace) {
        m.append(" ");
      }
      this->layers.push_back(m);
    }
  }
  void bump() {
    // TODO; determine visible layers
    // INPROGRESS; see YMOD
    for (unsigned int i=0; i<this->layers.size(); i++) {
      printl(
        i, 
        margin(MARGIN, layers.at(i))
      ); 
    }
  }
};
