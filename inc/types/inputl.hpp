#pragma once
#include "../screen.hpp"
#include <string>
#include <ncurses.h>

/** responsible for managing the input line */
struct inputl {
  std::string mbuff;
  unsigned int loffset = 5; // left offset
  unsigned int roffset = 3; // right offset
  unsigned int cindex = loffset; 
  void push(
    int c, // inputed character
    char mode[2] // mode signifier to print
  ) {   
    /** parse input character */
    switch(c) {
      case KEY_RIGHT:
        if ((cindex+1)-loffset <= mbuff.size()) {cindex++;}
        break;
      case KEY_LEFT:
        if (cindex-1 >= loffset) {cindex--;}
        break;
      case KEY_BACKSPACE:
        if (cindex-(loffset+1) >= mbuff.size()) {return;}
        cindex--;
        mbuff.erase(cindex-loffset, 1);
        break;
      case KEY_ENTER:
        /** new block */
        break;
      default:
        if (cindex-(loffset) >= mbuff.size()) {
          mbuff.resize(cindex-(loffset-1));
        }
        mbuff.at(cindex-loffset) = c;
        if (cindex+roffset != getmaxx(stdscr)) { // don't move the cursor if we're at the end
          cindex++;
        }
        break;
    }
    
    unsigned int mx = getmaxx(stdscr);
    /** fill in bar */
    char bump = ' ';
    unsigned int toffset = loffset+roffset; // total offset
    std::string fb; // 'final' buffer (e.g. display buffer)
    
    
    if (mx-(toffset) <= mbuff.size()) { // is the space available <= the size of the string
      bump = '}';
      fb = mbuff.substr(
          cindex-loffset-1, // current pos, -1 b/c of base 0
          mx-toffset // size avalible
        );
      cindex = mx-roffset-1; // TODO seems like the issue is visible here
    } else if (mbuff.size() != (mx-(toffset))) {
      fb = mbuff;
      /** fill out undersized buffer */
      while(fb.size() < mx-8) {
        fb.append(" ");
      }
    }
    
    /** print bar */
    printl(
      getmaxy(stdscr)-1,
      "| ", mode[0], mode[1], " ", fb, bump, " |"
    );
    move(getmaxy(stdscr)-1, cindex);
  }
};
