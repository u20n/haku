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
  /** ensure proper size */
  assert(getmaxx(stdscr) != sizeof...(t));
  /** pipe into string stream */
  std::stringstream sd;
  ((sd << t), ...);
  
  /** print line */
  mvprintw(yl, 0, sd.str().c_str());
}

