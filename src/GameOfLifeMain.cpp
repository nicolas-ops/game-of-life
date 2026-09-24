// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "GameOfLife.h"
#include "NcursesTerminalManager.h"

int main() {
  NcursesTerminalManager terminalManager;
  GameOfLife gameOfLife(terminalManager);
  gameOfLife.play();
}
