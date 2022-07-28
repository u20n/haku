#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/agent.hpp"
#include "inc/types/inputl.hpp"
#include "inc/types/splash.hpp"


int main(void) {
  agent a;
  inputl mbar(&a);
  bool close = false; // close flag
  
  char mode[2] = {'~', '>'};
  initscr();
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
  
  splash spl("./assets/bunny_splash");
  spl.show();
  while (!close) {
    refresh();
    /** handle input */
    int c = getch();
    mbar.bump(c, mode);
    refresh();
  }
  /** clean up */
  endwin();

  return 0;
}
