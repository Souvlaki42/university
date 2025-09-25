#include <iostream>
#include <vector>
#include <fstream>
#include <curses.h>
#include <sstream>

#include "character.h"
#include "scene.h"

using std::map, std::vector, std::string, std::ifstream, std::out_of_range, std::exception, std::runtime_error, std::ios, std::max, std::pair;

Scene::Scene(const string &map_path)
{
  if (map_path.size() > 4 && map_path.substr(map_path.size() - 4) == ".dat")
  {
    this->loadFromBinary(map_path);
  }
  else
  {
    this->loadFromText(map_path);
  }

  this->placeTileAtRandomCorridor(Tile::TRAP);
  this->placeTileAtRandomCorridor(Tile::TRAP);
  this->placeTileAtRandomCorridor(Tile::KEY);
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
  while ((this->get_tile(char1.get_position().x, char1.get_position().y) != Tile::CORRIDOR) ||
         (this->get_tile(char2.get_position().x, char2.get_position().y) != Tile::CORRIDOR) ||
         (abs(char2.get_position().x - char1.get_position().x) < 7 && abs(char2.get_position().y - char1.get_position().y) < 7))
  {
    char1.set_position();
    char2.set_position();
  }
}

void Scene::remove_obstacles(const Point &player1_pos, const Point &player2_pos)
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      Point current_pos = {(int)(x), (int)(y)};

      if (current_pos == player1_pos || current_pos == player2_pos)
        continue;

      const Tile tile = this->get_tile(x, y);
      if (tile == Tile::WALL || tile == Tile::TRAP || tile == Tile::CAGE)
      {
        this->set_tile(x, y, Tile::CORRIDOR);
      }
    }
  }
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
  if (y >= 0 && y < this->contents.size() &&
      x >= 0 && x < this->contents[y].size())
  {
    this->contents[y][x] = newTile;
  }
}

const Dimensions Scene::get_dimensions() const { return this->dimensions; }
const Point Scene::get_ladder_position() const { return this->ladder_pos; }

void Scene::loadFromText(const string &path)
{
  ifstream file(path);
  if (!file)
  {
    throw runtime_error("Αδυναμία ανοίγματος αρχείου χάρτη " + path);
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

    vector<Tile> row;
    row.reserve(map_width);
    for (size_t x_coord = 0; x_coord < line.length(); ++x_coord)
    {
      Tile tile = char_to_tile(line[x_coord]);
      row.push_back(tile);

      if (tile == Tile::LADDER)
      {
        this->ladder_pos = {int(x_coord), int(y_coord)};
      }
    }
    this->contents.push_back(row);
    y_coord++;
  }
  this->dimensions = {map_width, y_coord};

  if (this->dimensions.width <= 0 || this->dimensions.height <= 0)
  {
    throw runtime_error("Ο χάρτης είναι κενός ή μη έγκυρος.");
  }
}

void Scene::loadFromBinary(const string &path)
{
  ifstream file(path, ios::binary);
  if (!file)
  {
    throw runtime_error("Αδυναμία ανοίγματος δυαδικού αρχείου χάρτη " + path);
  }

  uint32_t width = 0, height = 0;
  file.read(reinterpret_cast<char *>(&width), sizeof(width));
  file.read(reinterpret_cast<char *>(&height), sizeof(height));

  if (!file)
  {
    throw runtime_error("Μη έγκυρη ή κατεστραμμένη κεφαλίδα στο δυαδικό αρχείο " + path);
  }

  this->dimensions = {width, height};

  if (this->dimensions.width <= 0 || this->dimensions.height <= 0)
  {
    throw runtime_error("Ο χάρτης είναι κενός ή μη έγκυρος.");
  }

  this->contents.resize(height, vector<Tile>(width));

  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      char tile_char;
      file.read(&tile_char, sizeof(tile_char));
      if (!file)
      {
        throw runtime_error("Ελλιπή δεδομένα χάρτη στο αρχείο " + path);
      }
      Tile tile = char_to_tile(tile_char);
      this->contents[y][x] = tile;

      if (tile == Tile::LADDER)
      {
        this->ladder_pos = {int(x), int(y)};
      }
    }
  }
}

void Scene::placeTileAtRandomCorridor(Tile tileToPlace)
{
  int safety_counter = 0;
  Point random_pos;
  do
  {
    random_pos.x = random() % this->dimensions.width;
    random_pos.y = random() % this->dimensions.height;
    safety_counter++;
    if (safety_counter > MAX_RAND_PLACEMENTS)
    {
      throw runtime_error("Δεν βρέθηκαν διάδρομοι για την τοποθέτηση των αντικειμένων.");
    }
  } while (get_tile(random_pos.x, random_pos.y) != Tile::CORRIDOR);

  set_tile(random_pos.x, random_pos.y, tileToPlace);
}