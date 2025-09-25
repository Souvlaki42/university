#include <vector>
#include <fstream>
#include <curses.h>

#include "character.h"
#include "scene.h"

using std::ifstream;
using std::ios;
using std::string;
using std::vector;

Scene::Scene(string map_path)
{
  if (map_path.size() > 4 && map_path.substr(map_path.size() - 4) == ".dat")
  {
    this->loadFromBinary(map_path);
  }
  else
  {
    this->loadFromText(map_path);
  }

  this->placeTileAtRandomCorridor(TILE_TRAP);
  this->placeTileAtRandomCorridor(TILE_TRAP);
  this->placeTileAtRandomCorridor(TILE_KEY);
}

void Scene::render()
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y + 1, x + 1, tile_to_char(this->contents[y][x]));
    }
  }
}

void Scene::place_characters(Character &char1, Character &char2)
{
  while ((this->get_tile(char1.get_position().x, char1.get_position().y) != TILE_CORRIDOR) ||
         (this->get_tile(char2.get_position().x, char2.get_position().y) != TILE_CORRIDOR) ||
         ((char2.get_position().x - char1.get_position().x < 7 && char2.get_position().x - char1.get_position().x > -7) && (char2.get_position().y - char1.get_position().y < 7 && char2.get_position().y - char1.get_position().y > -7)))
  {
    char1.set_position();
    char2.set_position();
  }
}

void Scene::remove_obstacles(Point player1_pos, Point player2_pos)
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      Point current_pos = {(int)(x), (int)(y)};

      if ((current_pos.x == player1_pos.x && current_pos.y == player1_pos.y) || (current_pos.x == player2_pos.x && current_pos.y == player2_pos.y))
        continue;

      int tile = this->get_tile(x, y);
      if (tile == TILE_WALL || tile == TILE_TRAP || tile == TILE_CAGE)
      {
        this->set_tile(x, y, TILE_CORRIDOR);
      }
    }
  }
}

int Scene::get_tile(int x, int y)
{
  if (y < 0 || y >= this->contents.size() ||
      x < 0 || x >= this->contents[y].size())
  {
    return TILE_NONE;
  }
  return this->contents[y][x];
}

void Scene::set_tile(int x, int y, int newTile)
{
  if (y >= 0 && y < this->contents.size() &&
      x >= 0 && x < this->contents[y].size())
  {
    this->contents[y][x] = newTile;
  }
}

Point Scene::get_dimensions() { return this->dimensions; }
Point Scene::get_ladder_position() { return this->ladder_pos; }

void Scene::loadFromText(string path)
{
  ifstream file(path);
  if (!file)
  {
    this->dimensions = {0, 0};
    return;
  }

  string line;
  size_t map_width = 0;
  size_t y_coord = 0;

  while (getline(file, line))
  {
    if (map_width == 0 && !line.empty())
    {
      map_width = line.length();
    }

    vector<int> row;
    row.reserve(map_width);
    for (size_t x_coord = 0; x_coord < line.length(); ++x_coord)
    {
      int tile = char_to_tile(line[x_coord]);
      row.push_back(tile);

      if (tile == TILE_LADDER)
      {
        this->ladder_pos = {int(x_coord), int(y_coord)};
      }
    }
    this->contents.push_back(row);
    y_coord++;
  }
  this->dimensions = {(int)map_width, (int)y_coord};
}

void Scene::loadFromBinary(string path)
{
  ifstream file(path, ios::binary);
  if (!file)
  {
    this->dimensions = {0, 0};
    return;
  }

  uint32_t width = 0, height = 0;
  file.read(reinterpret_cast<char *>(&width), sizeof(width));
  file.read(reinterpret_cast<char *>(&height), sizeof(height));

  if (!file)
  {
    this->dimensions = {0, 0};
    return;
  }

  this->dimensions = {(int)width, (int)height};

  this->contents.resize(height, vector<int>(width));

  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      char tile_char;
      file.read(&tile_char, sizeof(tile_char));
      if (!file)
      {
        this->dimensions = {0, 0};
        return;
      }
      int tile = char_to_tile(tile_char);
      this->contents[y][x] = tile;

      if (tile == TILE_LADDER)
      {
        this->ladder_pos = {int(x), int(y)};
      }
    }
  }
}

void Scene::placeTileAtRandomCorridor(int tileToPlace)
{
  Point random_pos;
  do
  {
    random_pos.x = random() % this->dimensions.x;
    random_pos.y = random() % this->dimensions.y;
  } while (get_tile(random_pos.x, random_pos.y) != TILE_CORRIDOR);

  set_tile(random_pos.x, random_pos.y, tileToPlace);
}