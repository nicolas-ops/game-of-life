// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#include "MockTerminalManager.h"
#include <string>

//_____________________________________________________________________________
MockTerminalManager::MockTerminalManager(int row, int col) {
  numRows_ = row;
  numCols_ = col;
}

//_____________________________________________________________________________
MockTerminalManager::~MockTerminalManager() {}

//____________________________________________________________________________
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) {
  Pixel pixel(row, col);
  PixelData data(inverse, intensity);
  pixelMap_[pixel] = data;
}

//____________________________________________________________________________
void MockTerminalManager::drawString(int row, int col, const char *output,
                                     float intensity) {
  Pixel pixel(row, col);

  std::string string(output);
  PixelData data(intensity, string);
  pixelMap_[pixel] = data;
}

//____________________________________________________________________________
bool MockTerminalManager::isPixelDrawn(int row, int col) const {
  return pixelMap_.count(Pixel{row, col});
}

//____________________________________________________________________________
bool MockTerminalManager::isPixelInverse(int row, int col) const {
  Pixel pixel(row, col);
  PixelData data = pixelMap_.at(pixel);
  return data.isInverse();
}

//____________________________________________________________________________
float MockTerminalManager::getIntensity(int row, int col) const {
  Pixel pixel(row, col);
  PixelData data = pixelMap_.at(pixel);
  return data.getIntensity();
}
