#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/overlay.hpp"

#include "inc/types/inputl.hpp"
#include "inc/types/history.hpp"
#include "inc/types/lsplash.hpp"


#include "assets/splash.hpp"

// still working this out
struct overlay_controller {
  mqueue mq;
}; 

int main(void) {  
  overlay_controller oc;
  history h;
  inputl mbar(&oc.mq);

  std::atomic<bool> close = false; // close flag
   
  initscr();
  use_default_colors(); // respect terminal color config first
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
   
  lsplash spl(mysplash);

  std::jthread st(&lsplash::play, &spl);
  st.detach(); 

  getch(); // "press any key to start"
  spl.halt(); // stop the splash screen
   
  while (!close) {
    /** show visually relevant info */
    mbar.show();
    h.show();
    move(getmaxy(stdscr)-1, mbar.actual); // update cursor pos
    
    /** handle input */
    int c = getch(); // slightly redundant, but we may need it later on
    mbar.bump(c);
  }

  /** clean up */
  endwin();

  return 0;
}
