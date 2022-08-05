#pragma once

#include <ranges>
#include <string_view>
#include <ncurses.h>

#include "../screen.hpp"

struct history {

  unsigned int MARGIN = 20;
  unsigned int YLVL = getmaxy(stdscr)-2;
  
  void sety(unsigned int y) {YLVL = y;}
  void setm(unsigned int m) {MARGIN = m;}

  void add_new(std::string m) {
    unsigned int mx = getmaxx(stdscr);
    unsigned int aspace = mx-(MARGIN*2);

    std::vector<std::string> words, layers;
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
        if (layers.at(lindex).size() + words.at(i).size() > aspace) {
          lindex++; // next layer
        } else {
          layers.at(lindex)+=words.at(i);
          i++;
        }
      }
    } else {
      // pad
      while(m.size() < aspace) {
        m.append(" ");
      }
      layers.push_back(m);
    }

    for (const auto& layer: layers) {
      printl(
        YLVL, 
        margin(MARGIN, layer)
      );
      YLVL--;
    }
  }
};
