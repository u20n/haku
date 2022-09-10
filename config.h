#pragma once
#include <ncurses.h>


/** 
 * just set with rgba
 * */
#define CHAT_FOREGROUND [0, 0, 0, 0]

// == MARGIN(s) == //
#define MARGIN 30

// == COMMAND KEYS == //
#define CMD_PREFIX ':'
#define CMD_BROWSE e
#define CMD_QUIT q

// == MOVEMENT KEYS == //
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT
#define MOVE_UP KEY_UP
#define MOVE_DOWN KEY_DOWN

inline char MODES[4][3] {
  {'~', '|', '>'}, // insert
  // browse
  {'^', '<', ']'}, // up
  {'v', '<', ']'}, // down
  {'(', ':', '<'} // change overlay
};
