#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>

#include "character.h"
#include "scene.h"

#define TERMINA 1000;

using std::cout, std::vector, std::string, std::ifstream, std::out_of_range;

Scene::Scene(const char *map_path) : moves(0), debug_msg("")
{
  this->file.open(map_path);
  string line;

  size_t y_coord = 0;
  size_t map_width = 0;
  while (getline(file, line))
  {
    size_t x_coord = 0;
    vector<Tile> row;

    if (map_width == 0 && !line.empty())
    {
      map_width = line.length();
    }

    for (const char &c : line)
    {
      Tile tile = static_cast<Tile>(c); //! IMPORTANT: static cast
      row.push_back(tile);

      if (tile == Tile::LADDER)
      {
        this->ladder_pos = Point{int(x_coord), int(y_coord)};
      }
      x_coord++;
    }

    this->contents.push_back(row);
    y_coord++;
  }
  this->dimensions = Dimensions{map_width, y_coord};

  Point tmp_pos = {0, 0};

  while (get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR)
  {
    tmp_pos.x = random() % this->dimensions.width;
    tmp_pos.y = random() % this->dimensions.height;
  }
  contents[tmp_pos.y][tmp_pos.x] = Tile::TRAP;

  while (get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR)
  {
    tmp_pos.x = random() % this->dimensions.width;
    tmp_pos.y = random() % this->dimensions.height;
  }
  contents[tmp_pos.y][tmp_pos.x] = Tile::TRAP;

  while (get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR)
  {
    tmp_pos.x = random() % this->dimensions.width;
    tmp_pos.y = random() % this->dimensions.height;
  }
  contents[tmp_pos.y][tmp_pos.x] = Tile::KEY;
}

Scene::~Scene()
{
  this->file.close();
}

const bool Scene::is_open() const
{
  return this->file.is_open();
}

const bool Scene::is_game_over(const char ch) const
{
  return ch == 'q' || this->moves > TERMINA;
}

void Scene::increment_moves()
{
  this->moves++;
}

void Scene::render()
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y, x, static_cast<char>(this->contents[y][x])); //! IMPORTANT: static cast
    }
  }

  mvaddstr(this->dimensions.height + 2, this->dimensions.width / 2, this->debug_msg.c_str());
}

const Dimensions Scene::get_dimensions() const
{
  return this->dimensions;
};

const Point Scene::get_ladder_position() const
{
  return this->ladder_pos;
}

const Tile Scene::get_tile(int x, int y) const
{
  if (y < 0 || y >= this->contents.size() ||
      x < 0 || x >= this->contents[y].size())
  {
    return Tile::NONE;
  }
  return this->contents[y][x];
}

void Scene::set_tile(int x, int y, const Tile &newTile)
{
  if (y < 0 || y >= this->contents.size() ||
      x < 0 || x >= this->contents[y].size())
  {
    throw out_of_range("set_tile: coordinates out of bounds");
  }
  this->contents[y][x] = newTile;
}

void Scene::debug(string message)
{
  this->debug_msg = message;
}