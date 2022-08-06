#pragma once

#include <ranges>
#include <string>
#include <ncurses.h>

#include "../screen.hpp"

struct history {
  unsigned int MARGIN = 50;
  unsigned int YMOD = 0; // y modifier, e.g. scroll distance
   
  void sety(unsigned int y) {YMOD = y;}
  void setm(unsigned int m) {MARGIN = m;}

  std::vector<std::string> layers;

  void add_new(std::string m) {
    unsigned int mx = getmaxx(stdscr);
    unsigned int aspace = mx-(MARGIN*2);

    if (m.size() > aspace) {
      // split
      std::vector<std::string> words;
      
      if (!m.find(" ")) {
        words.push_back(m);
      } else {
        std::stringstream sm{m};
        std::string tmp;
        while(getline(sm, tmp, ' ')) {
          words.push_back(tmp);
        }
      }

      unsigned int i, lindex = 0; // layer index
      while (i < words.size()) {
        if (words.at(i).size() > aspace) { // the word is too big, hypenate
          
          std::string big = words.at(i);

          // inject hypen
          big.insert(aspace-1, "-");
          
          words.at(i) = big.substr(0, aspace); // first part of the split
          words.insert(
            words.begin() + (i+1),
            big.substr(aspace, big.size())
          ); // rest
          continue; // try again 
        }
        
        if (layers.size() < lindex+1) { // new layer?
          layers.resize(lindex+1);
        }

        if ((layers.at(lindex).size() + words.at(i).size()) > aspace) {
          lindex++; // next layer
        } else {
          layers.at(lindex).append(words.at(i));
          i++;
        }
      }
      // pad when necessary
      for (unsigned int i=0; i<this->layers.size(); i++) {
        while(this->layers.at(i).size() < aspace) {
          this->layers.at(i).append(" ");
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
