#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/agent.hpp"
#include "inc/types/inputl.hpp"
#include "inc/types/history.hpp"
#include "inc/types/splash.hpp"

std::vector<std::string> mysplash {
  "       (*  >.<)",
  "        .haku!",
  " > press any key to start "
};

struct Client : public agent {
  history* h;
  void parse(std::string m) override {
 
  }

  void send(std::string m) override {
    h->add_new(m);
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
  
  std::atomic<bool> ready{true}; 
  splash spl(mysplash, &ready);
  ready.notify_all();
  spl.show();
  refresh();
  getch(); // "press any key to start"
  clear(); refresh();
  while (!close) {
    /** reset cursor */
    move(getmaxy(stdscr)-1, mbar.actual);

    /** handle input */
    mbar.show();
    int c = getch(); // slightly redundant, but we may need it later on
    mbar.bump(c);
    h.bump();
    refresh();
  }

  /** clean up */
  endwin();

  return 0;
}
