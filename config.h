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


// == MODE SIGNIFIERS == //
//char MODES[3][10] { 
//  {'-', '-', 'I', 'N', 'S', 'E', 'R', 'T', '-', '-'},
//  {'-', '-', ' ', 'V', 'I', 'E', 'W', ' ', '-', '-'},
//  {'-', '-', 'O', 'V', 'R', 'L', 'A', 'Y', '-', '-'}
//};
char MODES[3][2] {
  {'~', '>'}, // insert
  {' ', '%'}, // browse (the history panel) 
  {'(', '<'} // change overlay
};
