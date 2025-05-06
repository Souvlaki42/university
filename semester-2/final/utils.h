#ifndef UTILS
#define UTILS

typedef struct Point
{
  int x, y;
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

typedef struct Around
{
  Tile top, bottom, left, right, top_left, top_right, bottom_left, bottom_right;
} Around;

#endif