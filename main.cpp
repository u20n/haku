#include <ncurses.h>
#include <string>
#include <vector>

#include "inc/screen.hpp"
#include "inc/types/inputl.hpp"

/**
 * push a message to nodes
 *
 *
 * */
void push(std::string msg) {

}


int main(void) {
  /** 
   * content buffer 
   * we compute the visible portion of this @ runtime
   * 
   * message buffer
   * input buffer for user
   * */
  std::vector<std::string> cbuff;
  
  inputl mbar;
  bool close = false; // close flag
  unsigned int cindex = cbuff.size(); // index of the lowest "visible" message

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
