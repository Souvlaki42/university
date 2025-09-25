#include "utils.h"
#include <ostream>
#include <sstream>

bool Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const
{
  return !(*this == other);
}

bool Point::operator<(const Point &other) const
{
  if (y == other.y)
    return x < other.x;
  return y < other.y;
}

Point &Point::operator+=(const Point &other)
{
  this->x += other.x;
  this->y += other.y;
  return *this;
}

Point Point::operator+(const Point &other) const
{
  return {this->x + other.x, this->y + other.y};
}

char tile_to_char(Tile t)
{
  switch (t)
  {
  case Tile::WALL:
    return '*';
  case Tile::CORRIDOR:
    return ' ';
  case Tile::LADDER:
    return 'L';
  case Tile::KEY:
    return 'K';
  case Tile::TRAP:
    return 'T';
  case Tile::CAGE:
    return 'C';
  default:
    return '0';
  }
}

Tile char_to_tile(char c)
{
  switch (c)
  {
  case '*':
    return Tile::WALL;
  case ' ':
    return Tile::CORRIDOR;
  case 'L':
    return Tile::LADDER;
  case 'K':
    return Tile::KEY;
  case 'T':
    return Tile::TRAP;
  case 'C':
    return Tile::CAGE;
  default:
    return Tile::NONE;
  }
}