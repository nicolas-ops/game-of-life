// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "UserInput.h"
#include <ncurses.h>
//_____________________________________________________________________________
UserInput::UserInput() {
  keypad(stdscr, true);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
}
//_____________________________________________________________________________
int UserInput::getUserInput() {
  int input = getch();

  MEVENT event;
  if (input == KEY_MOUSE && getmouse(&event) == OK) {
    if (event.bstate & BUTTON1_PRESSED) {
      lastMouseRow_ = event.y;
      lastMouseCol_ = event.x / 2;
      return -2; // -2 should mean that the input was a mouse input.
    }
  }
  return input;
}
//_____________________________________________________________________________
int UserInput::getLastMouseRow() { return lastMouseRow_; }

//_____________________________________________________________________________
int UserInput::getLastMouseCol() { return lastMouseCol_; }
