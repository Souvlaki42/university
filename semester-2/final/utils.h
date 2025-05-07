#ifndef UTILS
#define UTILS

typedef struct Point
{
  int x, y;
  bool operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }
  bool operator<(const Point &other) const
  {
    if (y == other.y)
      return x < other.x;
    return y < other.y;
  }
} Point;

typedef struct Dimensions
{
  unsigned long width, height;
} Dimensions;

enum class Tile
{
  NONE = '0',
  WALL = '*',
  CORRIDOR = ' ',
  LADDER = 'L',
  KEY = 'K',
  TRAP = 'T',
};

typedef struct TileWithPosition
{
  Tile tile;
  Point position;
} TileWithPosition;

#endif