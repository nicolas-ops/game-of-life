// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#pragma once

#include "TerminalManager.h"

class NcursesTerminalManager : public TerminalManager {
public:
  // Constructor: initialize the terminal for use with ncurses.
  NcursesTerminalManager();

  // Destructor: Clean up the screen.
  ~NcursesTerminalManager();

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  void drawPixel(int row, int col, bool inverse, float intensity) override;

  // Draw a string at the given position and with the given intensity.
  // The intensity has to be in [0.0, 1.0]
  void drawString(int row, int col, const char *output,
                  float intensity = 1.0) override;

  // Refresh the screen.
  void refresh() override;

  // Get the number of colors.
  int numColors() override;

private:
  // Convert an intensity in the range [0.0, 1.0] to the index of the
  // corresponding color
  size_t convertIntensityToColor(float intensity) const;
};
