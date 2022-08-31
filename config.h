#pragma once
#include <ncurses.h>

/** 
 * just set with rgba
 * */
#define CHAT_FOREGROUND [0, 0, 0, 0]

// == OVERLAY KEYS == //
#define OVERLAY_CONTROL_TOGGLE KEY_HOME // toggle piping of command keys between overlay and haku

// == COMMAND KEYS == //
#define MODIFIER KEY_COMMAND
#define CMD_BROWSE e
#define CMD_OVERLAY q

// == MOVEMENT KEYS == //
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT
#define MOVE_UP KEY_UP
#define MOVE_DOWN KEY_DOWN

// == ESCAPE KEYS == //
int ESCAPE_INPUTL[3] = {':', 'q', 10};


// == MODE SIGNIFIERS == //
//char MODES[3][10] { 
//  {'-', '-', 'I', 'N', 'S', 'E', 'R', 'T', '-', '-'},
//  {'-', '-', ' ', 'V', 'I', 'E', 'W', ' ', '-', '-'},
//  {'-', '-', 'O', 'V', 'R', 'L', 'A', 'Y', '-', '-'}
//};
char MODES[4][3] {
  {'~', '|', '>'}, // insert
  // browse
  {'^', '<', ']'}, // up
  {'v', '<', ']'}, // down
  {'(', ':', '<'} // change overlay
};
