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
 * print, with color!
 */


/** 
 * apply a margin programatically equally to a buffer
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

/**
 * left margin, fill right
 * */
template<typename... T>
std::string lmargin(unsigned int margin, T... t) {
  unsigned int mx = getmaxx(stdscr);
  std::stringstream s;
  for (unsigned int i=0; i<margin; i++) {
    s << ' ';
  }
  ((s << t), ...);
  // fill in other side
  while (mx > s.str().size()) {
    s << ' ';
  }
  // no need to check s.str().size() == mx
  return s.str();
}

/**
 * print a blank line
 * */
std::string newl() {
  unsigned int mx = getmaxx(stdscr);
  std::string r;
  for (unsigned int i=0; i<mx; i++) {
    r.append(" ");
  };
  return r;
}
