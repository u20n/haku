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
    unsigned int aspace = mx-toffset; // avaliable space
    std::string fb; // 'final' buffer (e.g. display buffer)
     
    if (mbuff.size() >= aspace) { // is the msg longer than avalible?
      bump = '}';
      // TODO
      // this throws when you write over aspace,
      // and then go into the middle of the message,
      // and then start deleting
      // once you can see the first character, it gets an error,
      // this is because there's characters behind the cursor, but
      // we're essentially ignoring them for the fb compose 
      fb = mbuff.substr(
          cindex-(aspace-1), // current pos
          aspace // size avalible
        );
    } else if (mbuff.size() <= aspace) {
      fb = mbuff;
      /** fill out undersized buffer */
      while(fb.size() < aspace) {
        fb.append(" ");
      }
    }
    
    /** print bar */
    unsigned int acindex = cindex; // actual cursor index
    if (cindex >= aspace-1) {
      acindex = aspace-1;
    }
    acindex += loffset; // add offset
    
    printl(
      getmaxy(stdscr)-1,
      "| ", mode[0], mode[1], " ", fb, bump, " |"
    );
    move(getmaxy(stdscr)-1, acindex);
  }
};
