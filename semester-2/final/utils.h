#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <ostream>

struct Point
{
  int x, y;

  bool operator==(const Point &other) const;
  bool operator!=(const Point &other) const;
  bool operator<(const Point &other) const;
  Point &operator+=(const Point &other);
  Point operator+(const Point &other) const;
};

struct Dimensions
{
  size_t width, height;
};

enum class Tile
{
  NONE,
  WALL,
  CORRIDOR,
  LADDER,
  KEY,
  TRAP,
  CAGE,
};

enum class CharacterState
{
  EXPLORING,
  FETCHING_KEY,
  GOING_TO_CAGE,
  EXITING
};

std::wostream &operator<<(std::wostream &os, const Point &p);
std::wostream &operator<<(std::wostream &os, const CharacterState &s);

char tile_to_char(Tile t);

Tile char_to_tile(char c);

#endif