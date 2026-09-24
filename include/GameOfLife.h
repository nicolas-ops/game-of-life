// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#pragma once

#include "TerminalManager.h"
#include "UserInput.h"
#include <gtest/gtest_prod.h>

class GameOfLife {

private:
  static const int MAX_NUM_CELLS = 10'000;

  // Arrays which each hold the state of the Cells
  bool currentState_[MAX_NUM_CELLS];
  bool nextState_[MAX_NUM_CELLS];

  // Pointers to the Arrays which switch roles constantly
  bool *currentField_;
  bool *otherField_;

  // just a toggle to know which field to switch to next
  bool switchField_;

  // last mouse pos we get from UserInput
  int mouseClickRow_;
  int mouseClickCol_;

  // number of steps
  int completedSteps_;

  // number of alive cells
  int aliveCells_;

  // number of cols and rows
  int numCols_;
  int numRows_;

  // if step is true it will allow one simulation step to go before turning back
  // to false
  bool step_;

  // determines if the simulation is paused
  bool paused_;

  // determines if the game is running, if false the game will end.
  bool running_ = true;

  TerminalManager &tm_;

  UserInput userInput;

  // tests
  FRIEND_TEST(GameOfLifeTest, switchFields);
  FRIEND_TEST(GameOfLifeTest, numAliveNeighbors);
  FRIEND_TEST(GameOfLifeTest, updateState_underpopulation);
  FRIEND_TEST(GameOfLifeTest, updateState_reproduction);
  FRIEND_TEST(GameOfLifeTest, updateState_overpopulation);
  FRIEND_TEST(GameOfLifeTest, spawnGlider);

public:
  // Values get set and tm gets initialized
  GameOfLife(TerminalManager &tm);

  // initializes the terminal and holds the main while loop that runs the
  // simulation
  void play();

  // returns the number ob alive neighbours at a given cell
  int numAliveNeighbors(int row, int col);

  // Makes the simulation run by one step and saves it in the Fields
  void updateState();

  // shows whatever is in the field on the terminal
  void showState();

  // spawns a normal glider at a given position
  void spawnGlider(int row, int col);

  // sets the state of a Cell in a given state, position
  void setState(bool *field, int row, int col, bool state);

  // Takes the input from UserInput and does various kinds of things depending
  // on what key got presses, like pause, step, quit, spawnGLider and also
  // mouseclicks.
  void processUserInput();

  // Sets the field to random True False values.
  void fillPixelsRandomly();

  // returns the state of a cell on a given position
  bool getState(int row, int col);

  // switches the field, basically which array stores the current state and the
  // next state that will get shown next.
  void switchFields();
};
