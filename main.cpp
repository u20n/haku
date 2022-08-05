#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/agent.hpp"
#include "inc/types/inputl.hpp"
#include "inc/types/history.hpp"
#include "inc/types/splash.hpp"

struct Client : public agent {
  history h;
  void parse(std::string m) override {
 
  }

  void send(std::string m) override {
    h.add_new(m);
  }
};

int main(void) {
  inputl mbar(new Client);
  bool close = false; // close flag
   
  initscr();
  keypad(stdscr, TRUE); // enable function keys
	noecho(); // don't echo while getch
  
  splash spl("./assets/bunny_splash");
  spl.show();
  while (!close) {
    refresh();
    /** handle input */
    int c = getch();
    mbar.bump(c);
    refresh();
  }
  /** clean up */
  endwin();

  return 0;
}
