#pragma once
#include <cassert>
#include <sstream>


/**
 * generate an inputline for display
 * */
template<typename... T>
void printl(
  int yl, // what y to print @
  T... t // assorted types to print
) {
  /** pipe into string stream */
  std::stringstream sd;
  ((sd << t), ...);
  
  /** ensure proper size */
  assert((unsigned int) getmaxx(stdscr) == sd.str().length());
  /** print line */
  mvprintw(yl, 0, sd.str().c_str());
  refresh();
}


/** 
 * apply a margin programatically to a buffer
 * */
template<typename... T>
std::string margin(unsigned int margin, T... t) { 
  unsigned int mx = getmaxx(stdscr);
  std::stringstream s;
  
  // TODO; there's a better way to do this
  for (unsigned int i=0; i<margin; i++) {
    s << ' ';
  }
  
  ((s << t), ...);

  // goto 34, basically
  for (unsigned int i=0; i<margin; i++) {
    s << ' ';
  }

  assert(mx == s.str().length());
  return s.str();
}
