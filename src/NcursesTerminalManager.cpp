// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "NcursesTerminalManager.h"
#include <algorithm>
#include <cmath>
#include <ncurses.h>
#include <stdexcept>

static constexpr size_t systemColors = 16;

//____________________________________________________________________________
size_t NcursesTerminalManager::convertIntensityToColor(float intensity) const {
  intensity = 1 - std::exp(-50.0 * intensity);
  int color = (COLORS - 1 - systemColors) * std::clamp(intensity, 0.0f, 1.0f) +
              systemColors;
  return color;
}

//____________________________________________________________________________
NcursesTerminalManager::NcursesTerminalManager() {
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();

  if (COLORS < 200) {
    endwin();
    throw std::runtime_error{
        "The TerminalManager requires a terminal with"
        " at least 200 colors. Consider setting `TERM=xterm-256color` before"
        " starting the application"};
  }
  // Define as many shades of a certain color (red in this case) as there are
  // colors.
  for (int color = systemColors; color < COLORS; ++color) {
    int max = 800;
    int intensity = max * color / (COLORS - systemColors);
    init_color(color, intensity, 0, 0);
    // init_xcolor(color, intensity, 0, 0);
    init_pair(color, color, 0);
  }
  init_pair(0, COLOR_GREEN, COLOR_BLUE);

  numRows_ = LINES;
  numCols_ = COLS / 2;
}

//____________________________________________________________________________
NcursesTerminalManager::~NcursesTerminalManager() { endwin(); }

//____________________________________________________________________________
void NcursesTerminalManager::drawPixel(int row, int col, bool inverse,
                                       float intensity) {
  int color = convertIntensityToColor(intensity);
  if (inverse)
    attron(A_REVERSE);
  attron(COLOR_PAIR(color));
  mvprintw(row, 2 * col, "  ");
  attroff(COLOR_PAIR(color));
  if (inverse)
    attroff(A_REVERSE);
}

//____________________________________________________________________________
void NcursesTerminalManager::drawString(int row, int col, const char *output,
                                        float intensity) {
  int color = convertIntensityToColor(intensity);
  attron(COLOR_PAIR(color));
  mvaddstr(row, 2 * col, output);
  attroff(COLOR_PAIR(color));
}

//____________________________________________________________________________
void NcursesTerminalManager::refresh() { ::refresh(); }

//____________________________________________________________________________
int NcursesTerminalManager::numColors() { return COLORS; }
