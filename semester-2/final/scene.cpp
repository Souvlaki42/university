#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>

#include "character.h"
#include "scene.h"

using std::cout, std::vector, std::string, std::ifstream, std::out_of_range;

Scene::Scene(const char *map_path)
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

void Scene::render()
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y, x, static_cast<char>(this->contents[y][x])); //! IMPORTANT: static cast
    }
  }
}

const Dimensions Scene::get_dimensions() const
{
  return this->dimensions;
};

const Tile Scene::get_tile(int x, int y) const
{
  try
  {
    vector<Tile> row = this->contents.at(y);
    try
    {
      return row.at(x);
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