// Copyright (c) 2026 Nicolas Romanov. All Rights Reserved.

#pragma once

#include "TerminalManager.h"
#include <string>
#include <unordered_map>

// Class which stores the row and col coordinates to use as a key in the map
class Pixel {
public:
  Pixel(int y, int x) {
    x_ = x;
    y_ = y;
  }
  Pixel() = default;

  bool operator==(const Pixel &other) const {
    return getx() == other.getx() && gety() == other.gety();
  }

  int getx() const { return x_; }
  int gety() const { return y_; }

private:
  int x_ = 0;
  int y_ = 0;
};

// A custom hash function for the unordered map for using the Pixel class as a
// key
struct PixelHasher {
  size_t operator()(const Pixel &c) const {
    return std::hash<int>()(c.getx()) ^ (std::hash<int>()(c.gety()) << 1);
  }
};

// A Class to hold all the data that is usually shown on the screen but here its
// stored
class PixelData {
public:
  // Constructor for the drawString method
  PixelData(float intensity, std::string string)
      : intensity_(intensity), string_(string) {}

  // Constructor for the drawPixel method
  PixelData(bool inverse, float intensity)
      : inverse_(inverse), intensity_(intensity) {}
  PixelData() = default;

  bool isInverse() const { return inverse_; }

  float getIntensity() const { return intensity_; }

  std::string getString() const { return string_; }

private:
  bool inverse_ = false;
  float intensity_ = 0;
  std::string string_ = "";
};

class MockTerminalManager : public TerminalManager {

public:
  // Saves the number of cols and rows
  MockTerminalManager(int row, int col);

  ~MockTerminalManager();

  // Creates a PixelData object and puts the data inside a map to access later
  void drawPixel(int row, int col, bool inverse, float intensity) override;

  // Does the same as drawPixel but stores a string aswell
  void drawString(int row, int col, const char *output,
                  float intensity = 1.0) override;

  // Returns true if the given coordinates have a pixel in the map
  bool isPixelDrawn(int row, int col) const;

  // Returns true if the given coordinates have a pixel that is inversed
  bool isPixelInverse(int row, int col) const;

  // Returns the Intensity of the given coordinates pixel
  float getIntensity(int row, int col) const;

private:
  // Map which stores all the pixels
  std::unordered_map<Pixel, PixelData, PixelHasher> pixelMap_;
};
