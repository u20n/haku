#pragma once
#include "../screen.hpp"
#include "../push.hpp"

#include <string>
#include <charconv>
#include <ncurses.h>

char modes[3][2] = {
  {'~', '>'}, // insert
  {'>', '|'}, // edit
  {'|', '<'} // change view
};

/** responsible for managing the input line */
struct inputl {
  agent* uagent;
  std::string mbuff;
  unsigned int loffset = 5; // left offset
  unsigned int roffset = 3; // right offset
  unsigned int cindex = 0; // cursor index (on message)
  
  unsigned int actual = 0; // actual cursor pos

  int MARGIN = 30;
  
  enum modekey {
    INSERT,
    EDIT,
    VIEW
  };

  int mode = 0;

  void bump(int c) { // inputed character
    /** parse input character */
    switch(c) {
      case KEY_RIGHT:
        if (cindex == mbuff.size()) {return;}
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
        if (mbuff.empty()) {return;}
        // push new block
        uagent->send(std::string{mbuff});
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
    unsigned int toffset = loffset+roffset+(MARGIN*2); // total offset
    unsigned int aspace = mx-toffset; // avaliable space
    std::string fb; // 'final' buffer (e.g. display buffer)
    
    if (mbuff.size() >= aspace) { // is the msg longer than avalible?
      bump = '}';
      if (cindex <= aspace-1) { // should mbuff[0] be visable?  
        fb = mbuff.substr(
            0,
            aspace
        );
      } else { // cindex is in the middle, or the end of mbuff
        fb = mbuff.substr(
          (cindex-1) - (aspace-1), // first index
          aspace // size avaliable
        );
      }
    } else {
      fb = mbuff;
      /** fill out undersized buffer */
      while(fb.size() < aspace) {
        fb.append(" ");
      }
    }
    
    /** update cursor info */
    actual = cindex;
    if (cindex >= aspace-1) {
      actual = aspace-1;
    }
    actual += loffset+MARGIN; // add offset
     
    /** print bar */ 
    printl(
      getmaxy(stdscr)-1,
      margin(
        MARGIN,
        "| ", modes[mode][0], modes[mode][1], " ", fb, bump, " |"
      )
    );
    move(getmaxy(stdscr)-1, actual);
  }

  inputl(agent* ua) : uagent(ua) {}
};
