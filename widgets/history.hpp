#pragma once

#include <ranges>
#include <string>
#include <ncurses.h>

#include "../inc/screen.hpp"
#include "../inc/widget.hpp"


struct history : public widget {
  unsigned int MARGIN = 30;
  unsigned int YMOD = 0; // y modifier, e.g. scroll distance 

  std::vector<std::string> layers;

  void bump(std::string m) {
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
          words.push_back(tmp+=" ");
        }
      }

      unsigned int i = 0;
      unsigned int lindex = this->layers.size(); // layer index
      while (i < words.size()) {
        if (words.at(i).size() > aspace) { // the word is too big, hypenate 
          std::string big = words.at(i);

          big.insert(aspace-1, "-"); // inject hyphen
          words.at(i) = big.substr(0, aspace); // first part of the split
       
          words.resize(words.size()+1); // we're adding a new word
      
          words.insert(
            words.begin() + i+1, // behind i 
            big.substr(aspace-1, big.size()) // so we get '-' on the other side too
          ); // rest
          
          continue; // try again 
        }
        
        if (layers.size() < lindex+1) { // new layer?
          layers.resize(lindex+1);
        }

        if ((layers.at(lindex).size() + words.at(i).size()) > aspace) {
          lindex++; // next layer
          continue; // try again
        } 
        
        layers.at(lindex).append(words.at(i));
        i++;
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

  void show() {
    // TODO; determine visible layers
    // IN-PROGRESS; see YMOD
    
    // max y or layer count, whichever is smaller
    unsigned int my = getmaxy(stdscr);
    unsigned int off = (my-1 >= layers.size()) ? layers.size() : my-1;
    
    /**
     * this will 'yank' attention back to the most recent message, 
     * regardless of another setting
     * this is ok for now, when haku is being tested
     * but this should be changed in production
     * ~
     * control should be at main.cpp level
     * */
    YMOD = layers.size()-off;
                             
    for (unsigned int i=YMOD; i<off; i++) {
      printl(
        i-YMOD,
        margin(MARGIN, layers.at(i))
      ); 
    }
  }

  void bump(int char_code) override {
    switch(char_code) {
      case KEY_UP:
        if (this->YMOD+1 == layers.size()) return;
        this->YMOD++;
        break;
      case KEY_DOWN:
        if (this->YMOD == 0) return;
        this->YMOD--;
        break;
    }
    // scroll, etc (?)
  }
};
