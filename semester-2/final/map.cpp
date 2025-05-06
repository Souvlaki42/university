#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>

#include "character.h"
#include "map.h"

using std::cout, std::vector, std::string, std::ifstream, std::out_of_range;

Map::Map(const char *map_path)
{
  this->file.open(map_path);
  string input;
  unsigned long height = 0;
  while (getline(file, input))
  {
    height++;
    vector<char> line(input.begin(), input.end());
    vector<Tile> row;

    for (const char &c : line)
    {
      row.push_back(static_cast<Tile>(c)); //! IMPORTANT: static cast
    }

    this->contents.push_back(row);
  }
  this->dimensions = Dimensions{input.length(), height};

  Point tmp_random_position = {0, 0};

  while (get_tile(tmp_random_position) != Tile::CORRIDOR)
  {
    tmp_random_position.x = random() % this->dimensions.width;
    tmp_random_position.y = random() % this->dimensions.height;
  }
  contents[tmp_random_position.y][tmp_random_position.x] = Tile::TRAP;

  while (get_tile(tmp_random_position) != Tile::CORRIDOR)
  {
    tmp_random_position.x = random() % this->dimensions.width;
    tmp_random_position.y = random() % this->dimensions.height;
  }
  contents[tmp_random_position.y][tmp_random_position.x] = Tile::TRAP;

  while (get_tile(tmp_random_position) != Tile::CORRIDOR)
  {
    tmp_random_position.x = random() % this->dimensions.width;
    tmp_random_position.y = random() % this->dimensions.height;
  }
  contents[tmp_random_position.y][tmp_random_position.x] = Tile::KEY;
}

Map::~Map()
{
  this->file.close();
}

const bool Map::is_open() const
{
  return this->file.is_open();
}

void Map::render()
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y, x, static_cast<char>(this->contents[y][x])); //! IMPORTANT: static cast
    }
  }
}

const Dimensions Map::get_dimensions() const
{
  return this->dimensions;
};

const Tile Map::get_tile(Point position) const
{
  try
  {
    vector<Tile> row = this->contents.at(position.y);
    try
    {
      return row.at(position.x);
    }
    catch (out_of_range e)
    {
      return Tile::NONE;
    }
  }
  catch (out_of_range e)
  {
    return Tile::NONE;
  };
}