// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#pragma once

class UserInput {
private:
  // Last mouse click positions
  int lastMouseRow_;
  int lastMouseCol_;

public:
  // constructor where additional terminal things get initialized
  UserInput();

  // returns the user input. if its a mouse input it returns -2 and sets the
  // last mouse pos
  int getUserInput();

  // Returns the last mouse pos
  int getLastMouseRow();
  int getLastMouseCol();
};
