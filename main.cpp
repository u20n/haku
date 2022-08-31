#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/overlay.hpp"
#include "inc/inputd.hpp"


#include "widgets/focus.hpp"
#include "widgets/inputl.hpp"
#include "widgets/history.hpp"
#include "widgets/lsplash.hpp"

#include "assets/splash.hpp"

// still working this out
struct overlay_controller {
  mqueue mq;
};

int main(void) {  
  overlay_controller oc;
  
  // widgits
  history h;
  inputl mb(&oc.mq);
  focus f(&h, &mb);
  // input daemon
  inputd idaemon {
    {
    {&f, {}},
    {&mb, {':', 'q', 10}},
    {&h, {'q'}} 
    }
  };
  idaemon.focus(&mb);
  
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
    mb.show();
    h.show();
    move(getmaxy(stdscr)-1, mb.actual); // update cursor pos TODO migrate somewhere within idaemon
    
    /** handle input */
    idaemon.cycle(getch()); 
  }

  /** clean up */
  endwin();

  return 0;
}
