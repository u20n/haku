#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/types/inputl.hpp"

int main(void) {
  inputl mbar;
  bool close = false; // close flag
  
  char mode[2] = {'~', '>'};
  initscr();
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
  

  while (!close) {
    refresh();
    /** handle input */
    int c = getch();
    mbar.push(c, mode);
    refresh();
  }
  /** clean up */
  endwin();

  return 0;
}
