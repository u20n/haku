#pragma once
#include "../screen.hpp"
#include <string>
#include <charconv>
#include <ncurses.h>


/** responsible for managing the input line */
struct inputl {
  std::string mbuff;
  unsigned int loffset = 5; // left offset
  unsigned int roffset = 3; // right offset
  unsigned int cindex = 0; // cursor index (on message)
  
  void push(
    int c, // inputed character
    char mode[2] // mode signifier to print
  ) {   
    /** parse input character */
    switch(c) {
      case KEY_RIGHT:
        if (cindex == (mbuff.size()-1)) {return;}
        cindex++;
        break;
      case KEY_LEFT:
        if (cindex-1 >= 0) {cindex--;}
        break;
      case KEY_BACKSPACE:
        if (cindex == 0) {return;}
        cindex--;
        mbuff.erase(cindex, 1);
        break;
      case KEY_ENTER:
        /** new block */
        break;
      default:
        if (cindex >= mbuff.size()) {
          mbuff.resize(cindex+1);
        }
        // TODO
        // if the editing mode is (intended) insert, this overwrites
        mbuff.at(cindex) = c;
        cindex++;
        break;
    }
    
    unsigned int mx = getmaxx(stdscr);
    /** fill in bar */
    char bump = ' ';
    unsigned int toffset = loffset+roffset; // total offset
    std::string fb; // 'final' buffer (e.g. display buffer)
    
    if (mbuff.size() >= mx-toffset) { // is the space available <= the size of the string
      bump = '}';
      fb = mbuff.substr(
          cindex, // current pos
          mx-toffset // size avalible
        );
    } else if (mbuff.size() <= mx-toffset) {
      fb = mbuff;
      /** fill out undersized buffer */
      while(fb.size() < mx-toffset) {
        fb.append(" ");
      }
    }
    
    /** print bar */
    unsigned int acindex = cindex; // actual cursor index
    if (cindex >= mx-toffset) {
      acindex = mx-toffset;
    } else {
      acindex += loffset; // add offset
    }
    printl(
      getmaxy(stdscr)-1,
      "| ", mode[0], mode[1], " ", fb, bump, " |"
    );
    move(getmaxy(stdscr)-1, acindex);
  }
};
