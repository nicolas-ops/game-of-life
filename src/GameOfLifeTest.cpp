// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "GameOfLife.h"
#include "MockTerminalManager.h"
#include "gtest/gtest.h"

MockTerminalManager tm = MockTerminalManager(100, 100);
GameOfLife gol = GameOfLife(tm);

TEST(GameOfLifeTest, switchFields) {
  ASSERT_EQ(gol.currentState_, gol.currentField_);
  ASSERT_EQ(gol.nextState_, gol.otherField_);
  ASSERT_FALSE(gol.switchField_);

  gol.switchFields();

  ASSERT_EQ(gol.nextState_, gol.currentField_);
  ASSERT_EQ(gol.currentState_, gol.otherField_);
  ASSERT_TRUE(gol.switchField_);
}

TEST(GameOfLifeTest, numAliveNeighbors) {
  gol.numCols_ = 10;
  gol.numRows_ = 10;

  for (int r = 0; r <= gol.numRows_; r++) {
    for (int c = 0; c <= gol.numCols_; c++) {
      gol.setState(gol.currentField_, r, c, false);
    }
  }

  gol.setState(gol.currentField_, 1, 1, true);
  gol.setState(gol.currentField_, 1, 2, true);
  gol.setState(gol.currentField_, 2, 1, true);

  ASSERT_EQ(gol.numAliveNeighbors(2, 2), 3);
  ASSERT_EQ(gol.numAliveNeighbors(0, 0), 1);
  ASSERT_EQ(gol.numAliveNeighbors(5, 5), 0);
}

TEST(GameOfLifeTest, updateState_underpopulation) {
  gol.numCols_ = 10;
  gol.numRows_ = 10;

  for (int r = 0; r <= gol.numRows_; r++) {
    for (int c = 0; c <= gol.numCols_; c++) {
      gol.setState(gol.currentField_, r, c, false);
    }
  }

  gol.setState(gol.currentField_, 5, 5, true);

  gol.updateState();

  ASSERT_FALSE(gol.getState(5, 5));
}

TEST(GameOfLifeTest, updateState_reproduction) {
  gol.numCols_ = 10;
  gol.numRows_ = 10;

  for (int r = 0; r <= gol.numRows_; r++) {
    for (int c = 0; c <= gol.numCols_; c++) {
      gol.setState(gol.currentField_, r, c, false);
    }
  }

  gol.setState(gol.currentField_, 5, 4, true);
  gol.setState(gol.currentField_, 5, 5, true);
  gol.setState(gol.currentField_, 5, 6, true);

  gol.updateState();

  ASSERT_TRUE(gol.getState(4, 5));
  ASSERT_TRUE(gol.getState(5, 5));
  ASSERT_TRUE(gol.getState(6, 5));
  ASSERT_FALSE(gol.getState(5, 4));
  ASSERT_FALSE(gol.getState(5, 6));
}

TEST(GameOfLifeTest, updateState_overpopulation) {
  gol.numCols_ = 10;
  gol.numRows_ = 10;

  for (int r = 0; r <= gol.numRows_; r++) {
    for (int c = 0; c <= gol.numCols_; c++) {
      gol.setState(gol.currentField_, r, c, false);
    }
  }

  gol.setState(gol.currentField_, 5, 5, true);
  gol.setState(gol.currentField_, 4, 5, true);
  gol.setState(gol.currentField_, 6, 5, true);
  gol.setState(gol.currentField_, 5, 4, true);
  gol.setState(gol.currentField_, 5, 6, true);

  gol.updateState();

  ASSERT_FALSE(gol.getState(5, 5));
}

TEST(GameOfLifeTest, spawnGlider) {
  gol.numCols_ = 20;
  gol.numRows_ = 20;

  for (int r = 0; r <= gol.numRows_; r++) {
    for (int c = 0; c <= gol.numCols_; c++) {
      gol.setState(gol.currentField_, r, c, false);
    }
  }

  gol.spawnGlider(5, 5);

  ASSERT_FALSE(gol.getState(5, 5));
  ASSERT_TRUE(gol.getState(4, 5));
  ASSERT_TRUE(gol.getState(5, 6));
  ASSERT_TRUE(gol.getState(6, 4));
  ASSERT_TRUE(gol.getState(6, 5));
  ASSERT_TRUE(gol.getState(6, 6));
}
