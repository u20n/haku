#pragma once
#include "../screen.hpp"
#include "../push.hpp"
#include "../../config.h"

#include <string>
#include <charconv>
#include <ncurses.h>

/** responsible for managing the input line */
struct inputl {
  mqueue* mq; // outgoing messages
  std::string mbuff;  
  unsigned int cindex = 0; // cursor index (on message)
  
  int MARGIN = 30;
  
  unsigned int actual = MARGIN+sizeof(MODES[0])+cindex; // actual cursor x index (on screen)

  enum modekey {
    INSERT,
    BROWSE,
    VIEW
  };

  int mode = 0;
  
  void show() { 
    unsigned int mx, my;
    getmaxyx(stdscr, my, mx);

    /** determine how much space we're working with */
    std::string mstr{MODES[mode], sizeof(MODES[mode])};
    unsigned int loffset = mstr.size()+1; // one space
    unsigned int roffset = 2; // bump, space

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
      my-1,
      margin(
        MARGIN,
        mstr, " ", fb, bump, " "
      )
    );
  }

  void bump(int c) { // inputed character
    /** parse input character */
    switch(c) {
      case MODIFIER:
        // do modifier stuff 
        break;
      case MOVE_RIGHT:
        if (cindex == mbuff.size()) {return;}
        cindex++;
        break;
      case MOVE_LEFT:
        if (cindex-1 >= 0) {cindex--;}
        break;
      case KEY_BACKSPACE:
        if (cindex == 0) {return;}
        cindex--;
        mbuff.erase(cindex, 1);
        break;
      case KEY_DC:
        if (mbuff.size() == 0) {return;}
        // unfortunately seems like no cleaner way to do this
        if (cindex+1 > mbuff.size()) { // we're past the end
          mbuff.pop_back();
          cindex--;
        } else if (cindex+1 == mbuff.size()) { // we're at the end
          mbuff.pop_back();
        } else if (cindex+1 < mbuff.size()) { // we're inside
          mbuff.erase(cindex+1, 1);
        }
        break;
      case 10: // to catch keyboard enter
      case KEY_ENTER:
        if (mbuff.empty()) {return;}
        // push new block
        mq->queue.push_back(std::string{mbuff});
        mq->notify();
        cindex = 0; mbuff.clear(); // reset 
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
  }
  
  inputl(mqueue* mq) : mq(mq) {}
};
