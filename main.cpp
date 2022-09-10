#include <ncurses.h>
#include <string>
#include <vector>
#include <atomic>

#include "inc/screen.hpp"

#include "inc/inputl.hpp"
#include "inc/history.hpp"

int main(void) {    
  // widgits
  history h;
  inputl mb(&h);

  std::atomic<bool> close = false; // close flag
   
  initscr();
  use_default_colors(); // respect terminal color config first
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
   
  while (!close) {
    /** show visually relevant info */
    mb.show();
    h.show();
    move(getmaxy(stdscr)-1, mb.actual);    
    
    /** handle input */
    mb.bump(getch()); 
  }

  /** clean up */
  endwin();

  return 0;
}
