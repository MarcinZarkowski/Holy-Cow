//
// Created by Marcin Zarkowski on 12/11/25.
//

#include "Map.h"
#include "Cell.h"
#include "pch.h"
#include <ctime>
#include <vector>

Map::Map(int mapDimensions) {
  mMapSize = mapDimensions;
  std::srand(std::time(0));
  mMap = std::vector<std::vector<Cell>>(
      mapDimensions, std::vector<Cell>(mapDimensions, Cell(CellType::Wall)));

  int startx = rand() % mMap.size();
  int starty = rand() % mMap[0].size();
  int endx = rand() % mMap.size();
  int endy = rand() % mMap[0].size();

  mStartCoords = {startx, starty};
  mEndCoords = {endx, endy};

  CreatePath(startx, starty, endx, endy);
  AddDangers();
  AddNoise();
}

void Map::CreatePath(int startX, int startY, int endX, int endY) {
  int x = startX;
  int y = startY;
  mMap[y][x].setType(CellType::Walkable);

  while (x != endX || y != endY) {
    int closingDimension = rand() % 2;
    int nextX = x;
    int nextY = y;

    if (closingDimension == 0) {
      if (y < endY)
        nextY++;
      else if (y > endY)
        nextY--;
      else
        nextX += (rand() % 2 == 0) ? 1 : -1;
    } else {
      if (x < endX)
        nextX++;
      else if (x > endX)
        nextX--;
      else
        nextY += (rand() % 2 == 0) ? 1 : -1;
    }

    if (nextX >= 0 && nextX < mMapSize && nextY >= 0 && nextY < mMapSize) {
      x = nextX;
      y = nextY;
      mMap[y][x].setType(CellType::Walkable);
    }
  }
  mMap[endY][endX].setType(CellType::Destination);
}

void Map::AddDangers() {
  for (int y = 0; y < mMap.size(); ++y) {
    for (int x = 0; x < mMap[0].size(); ++x) {
      if (mMap[y][x].getType() == CellType::Wall && rand() % 75 == 0) {
        mMap[y][x].setType(CellType::Turret);
      }
    }
  }
}

void Map::AddNoise() {
  for (int y = 0; y < mMap.size(); ++y) {
    for (int x = 0; x < mMap[0].size(); ++x) {
      if (mMap[y][x].getType() == CellType::Wall) {
        int roll = rand() % 6; // 0-5
        if (roll < 3) {        // 50% chance (0,1,2)
          mMap[y][x].setType(CellType::Walkable);
        } else if (roll == 3) { // ~17% chance haystack
          mMap[y][x].setType(CellType::HayStack);
        }
        // else stays as wall (33% chance)
      }
    }
  }
}

int Map::dimensions() { return mMapSize; }

const std::vector<int> &Map::getStartCoords() { return mStartCoords; }

const std::vector<int> &Map::getEndCoords() { return mEndCoords; }

Cell &Map::at(int x, int y) { return mMap[y][x]; }