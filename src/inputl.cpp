#include "../inc/inputl.hpp"
#include "../config.h"

void inputl::cmd_parse() {
  
}

void inputl::push(int c) {
  if (cindex >= mbuff.size()) {
    mbuff.resize(cindex+1);
  }
  // TODO
  // if the editing mode is (intended) insert, this overwrites
  mbuff.at(cindex) = c;
  cindex++;
}

void inputl::bump(int c) { // inputed character
  /** parse input character */
  if (this->cmd_active) {
    if (c == KEY_ENTER || c == 10) {
      this->cmd_parse();
      this->cmd_active = false;
    } else {
      this->cmd_buff.push_back(c);
    }
  } 
  switch(c) {
    case CMD_PREFIX:
      // divert incoming
      if (this->mbuff.size() < 1) {
        this->cmd_active = true;
      }
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
      {
      if (mbuff.empty() || mbuff.at(0) == CMD_PREFIX) {return;}
      // push to UNIX port (TODO)
      mbuff.clear(); cindex = 0; // reset
      break;
      }
    default:
      this->push(c); 
  }
}

void inputl::show() { 
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
    actual = (cindex >= aspace-1) ? aspace : cindex;
    actual += loffset+MARGIN; // add offset
     
    /** print bar */ 
    scr::printl(
      my-1,
      scr::margin(
        MARGIN,
        mstr, " ", fb, bump, " "
      )
    );
  }
