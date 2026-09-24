// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#pragma once
#include <cstddef>

class TerminalManager {
public:
  TerminalManager() : numRows_(0), numCols_(0) {}

  virtual ~TerminalManager() {}

  virtual void drawPixel(int row, int col, bool inverse, float intensity) = 0;

  virtual void drawString(int row, int col, const char *characters,
                          float intensity = 1.0) = 0;
  virtual void refresh() {}

  // Get the dimensions of the screen.
  int numRows() const { return numRows_; }
  int numCols() const { return numCols_; }

  virtual int numColors() { return 0; }

protected:
  // The number of rows and columns of the screen.
  int numRows_;
  int numCols_;
};
