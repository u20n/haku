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
        cindex++;
        break;
      case KEY_LEFT:
        cindex--;
        break;
      case KEY_BACKSPACE:
        if (cindex-(loffset+1) >= mbuff.size()) {return;}
        cindex--;
        mbuff.erase(cindex-loffset);
        break;
      case KEY_ENTER:
        /** new block */
        break;
      default:
        if (cindex-(loffset) >= mbuff.size()) {
          mbuff.resize(cindex-(loffset-1));
        }
        mbuff.at(cindex-loffset) = c;
        cindex++;
        break;
    }
    
    unsigned int mx = getmaxx(stdscr);
    /** fill in bar */
    char bump = ' ';
    unsigned int toffset = loffset+roffset; // total offset
    std::string fb; // 'final' buffer (e.g. display buffer)
    
    if (mx-(toffset) <= mbuff.size()+1) {
      bump = '}';
      fb = mbuff.substr(
          mx-(toffset)-1,
          cindex-(toffset)-1
        );
      cindex = fb.size()+loffset-1;
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
