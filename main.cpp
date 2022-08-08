#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/agent.hpp"

#include "inc/types/inputl.hpp"
#include "inc/types/history.hpp"
#include "inc/types/asplash.hpp"


#include "assets/splash.hpp"

struct Client : public agent {
  history* h;
  void parse(std::string m) override {
 
  }

  void send(std::string m) override {
    h->bump(m);
  }
  Client(history* h) : h(h) {}
};

int main(void) {
  history h;
  inputl mbar(new Client{&h});

  std::atomic<bool> close = false; // close flag
   
  initscr();
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
   
  asplash spl(mysplash);

  std::jthread jt{&asplash::play, &spl};
  jt.detach();
  while (!spl.stop) {
    refresh();
    clear();
  }

  getch(); // "press any key to start"
  clear(); refresh();

  mbar.show(); h.show(); // jump start (TODO; make more elegant)
  while (!close) { 
    /** handle input */
    int c = getch(); // slightly redundant, but we may need it later on
    mbar.bump(c);

    /** show relevant info */
    mbar.show();
    h.show();
      
    /** reset cursor */
    move(getmaxy(stdscr)-1, mbar.actual); // kinda hacky TODO    
    
    refresh();
  }

  /** clean up */
  endwin();

  return 0;
}
