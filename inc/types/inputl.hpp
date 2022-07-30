#pragma once
#include "../screen.hpp"
#include "../push.hpp"
#include <string>
#include <charconv>
#include <ncurses.h>

/** responsible for managing the input line */
struct inputl {
  agent* uagent;
  std::string mbuff;
  unsigned int loffset = 5; // left offset
  unsigned int roffset = 3; // right offset
  unsigned int cindex = 0; // cursor index (on message)
  
  void bump(
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
      case KEY_DC:
        if (cindex == mbuff.size()-1) {
          mbuff.erase(cindex, 1);
          cindex--;
        } else {
          mbuff.erase(cindex+1, 1);
        }
        break;
      case 10: // to catch keyboard enter
      case KEY_ENTER:
        // push new block
        uagent->send(mbuff);
        cindex = 0;
        mbuff.clear();
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
      if (cindex >= mbuff.size()-1) { // is cindex @ the end of msg buffer
        fb = mbuff.substr(
          cindex-(aspace-1), // current pos
          aspace // size avalible
        );
      } else if (cindex <= aspace-1) { // should mbuff[0] be visable?  
        fb = mbuff.substr(
            0,
            aspace
          );
      }
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

  inputl(agent* ua) : uagent(ua) {}
};
