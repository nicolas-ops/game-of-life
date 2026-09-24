// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "GameOfLife.h"
#include "TerminalManager.h"
#include "UserInput.h"
#include <cstdlib>
#include <unistd.h>

//_____________________________________________________________________________
GameOfLife::GameOfLife(TerminalManager &tm) : tm_{tm} {

  numRows_ = tm_.numRows();
  numCols_ = tm_.numCols();

  currentField_ = currentState_;
  otherField_ = nextState_;

  paused_ = false;
}

//_____________________________________________________________________________
void GameOfLife::play() {

  while (running_) {
    processUserInput();
    showState();

    if (!paused_ || step_) {
      updateState();
      step_ = false;
      completedSteps_++;
    }

    usleep(50000);
  }
}

//_____________________________________________________________________________
void GameOfLife::processUserInput() {
  int keycode = userInput.getUserInput();

  if (keycode == -2) {

    mouseClickRow_ = userInput.getLastMouseRow();
    mouseClickCol_ = userInput.getLastMouseCol();

    bool state = getState(mouseClickRow_, mouseClickCol_);
    setState(currentField_, mouseClickRow_, mouseClickCol_, !state);
    showState();
    return;
  }

  switch (keycode) {

  case (32):
    paused_ = !paused_;
    break;
  case (115):
    step_ = true;
    break;
  case (114):
    fillPixelsRandomly();
    break;
  case (113):
    running_ = false;
    break;
  case (103):
    spawnGlider(mouseClickRow_, mouseClickCol_);
    break;
  default:
    break;
  }
}
//_____________________________________________________________________________
int GameOfLife::numAliveNeighbors(int row, int col) {
  int count = 0;
  for (int x = col - 1; x <= col + 1; x++) {
    for (int y = row - 1; y <= row + 1; y++) {
      if (x < 0 || y < 0 || x >= numCols_ || y >= numRows_) {
        continue;
      }
      if (y == row && x == col) {
        continue;
      }
      if (getState(y, x)) {
        count++;
      }
    }
  }
  return count;
}
//_____________________________________________________________________________
void GameOfLife::showState() {
  aliveCells_ = 0;
  for (int row = 0; row < numRows_; row++) {
    for (int col = 0; col < numCols_; col++) {
      bool state = getState(row, col);
      int color = state ? 1 : -1;
      tm_.drawPixel(row, col, true, color);
      if (state) {
        aliveCells_++;
      }
    }
  }
  tm_.refresh();
}
//_____________________________________________________________________________
void GameOfLife::updateState() {
  for (int row = 0; row < numRows_; row++) {
    for (int col = 0; col < numCols_; col++) {
      bool alive = getState(row, col);
      int neighbours = numAliveNeighbors(row, col);
      if (alive) {
        if (neighbours < 2 || neighbours > 3) {
          setState(otherField_, row, col, false);
        } else {
          setState(otherField_, row, col, true);
        }
      } else {
        if (neighbours == 3) {
          setState(otherField_, row, col, true);
        } else {
          setState(otherField_, row, col, false);
        }
      }
    }
  }
  switchFields();
}
//_____________________________________________________________________________
void GameOfLife::spawnGlider(int row, int col) {
  if (row + -1 < 0 || col - 1 < 0 || row + 1 > numRows_ || col + 1 > numCols_) {
    return; // cursor is out of bounds and will throw an error if not returned;
  }
  setState(currentField_, row, col, false);
  setState(currentField_, row - 1, col + 0, true);
  setState(currentField_, row + 0, col + 1, true);
  setState(currentField_, row + 1, col - 1, true);
  setState(currentField_, row + 1, col + 0, true);
  setState(currentField_, row + 1, col + 1, true);
}

//_____________________________________________________________________________
void GameOfLife::switchFields() {
  bool *temp = currentField_;
  currentField_ = otherField_;
  otherField_ = temp;
  switchField_ = !switchField_;
}
//_____________________________________________________________________________
void GameOfLife::fillPixelsRandomly() {
  for (int row = 0; row < numRows_; ++row) {
    for (int col = 0; col < numCols_; ++col) {
      setState(otherField_, row, col, rand() % 5 == 0);
    }
  }
  switchFields();
}
//_____________________________________________________________________________
void GameOfLife::setState(bool *field, int row, int col, bool state) {
  field[row * numCols_ + col] = state;
}
//_____________________________________________________________________________
bool GameOfLife::getState(int row, int col) {
  return currentField_[row * numCols_ + col];
}
