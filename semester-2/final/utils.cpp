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

std::wostream &operator<<(std::wostream &os, const Point &p)
{
  os << L"(" << p.x << L", " << p.y << L")";
  return os;
}

std::wostream &operator<<(std::wostream &os, const CharacterState &s)
{
  switch (s)
  {
  case CharacterState::EXPLORING:
    os << L"Εξερευνώ...";
    break;
  case CharacterState::FETCHING_KEY:
    os << L"Πάω να πάω το κλειδί...";
    break;
  case CharacterState::GOING_TO_CAGE:
    os << L"Πάω να ξεκλειδώσω το κλουβί...";
    break;
  case CharacterState::GOING_TO_LADDER:
    os << L"Πάω στην σκάλα...";
    break;
  case CharacterState::IDLE:
    os << L"Δεν κάνω τίποτα...";
    break;
  default:
    os << L"Λάθος κατάσταση";
    break;
  }
  return os;
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

std::wstring make_char_key(const std::wstring &base_text, char symbol)
{
  std::wstringstream ss;
  ss << base_text << L" (" << symbol << L')';
  return ss.str();
}