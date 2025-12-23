//
// Created by Marcin Zarkowski on 12/20/25.
//

#pragma once
#include "Cell.h"
#include "pch.h"

class Map {
public:
  Map() = default;
  Map(int mapDimensions);
  Cell &at(int x, int y);
  int dimensions();
  const std::vector<int> &getStartCoords();
  const std::vector<int> &getEndCoords();

private:
  int mMapSize = 128;
  std::vector<int> mStartCoords;
  std::vector<int> mEndCoords;

  std::vector<std::vector<Cell>> mMap;

  void CreatePath(int startx, int starty, int endx, int endy);
  void AddDangers();
  void AddNoise();
};
