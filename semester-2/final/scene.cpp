#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>

#include "character.h"
#include "scene.h"

#define TERMINA 1000

using std::cout, std::vector, std::string, std::ifstream, std::out_of_range;

Scene::Scene(const char *map_path) : moves(0), debug_msg(""), running(true), winning(false)
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
  if (this->winning)
  {
    cout << "Τελικά βρεθήκαν οι χαρακτήρες και το βασίλειο σώθηκε. Πέρασαν " << this->moves << " τέρμινα.\n";
  }
  else
  {
    cout << "Τελικά δεν βρεθήκαν οι χαρακτήρες και το βασίλειο χάθηκε. Πέρασαν " << this->moves << " τέρμινα.\n";
  }
}

const bool Scene::is_open() const
{
  return this->file.is_open();
}

const bool Scene::is_winning() const
{
  return this->winning;
}

const bool Scene::is_running() const
{
  return this->running;
}

void Scene::update()
{
  this->moves++;
  if (getch() == 'q' || this->moves >= TERMINA)
  {
    this->set_winning(false);
    this->set_running(false);
  }
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
    throw out_of_range("Σφάλμα: Λάθος συντεταγμένες.");
  }
  this->contents[y][x] = newTile;
}

void Scene::set_winning(const bool winning)
{
  if (winning)
  {
    this->clear_maze();
  }

  this->winning = winning;
}

void Scene::set_running(const bool running)
{
  this->running = running;
}

void Scene::clear_maze()
{
  try
  {
    for (size_t y = 0; y < this->contents.size(); ++y)
    {
      for (size_t x = 0; x < this->contents[y].size(); ++x)
      {
        const Tile tile = this->contents[y][x];
        if (tile == Tile::CAGE || tile == Tile::TRAP || tile == Tile::WALL)
        {
          this->set_tile(x, y, Tile::CORRIDOR);
        }
      }
    }
  }
  catch (const std::exception &e)
  {
    this->debug(e.what());
  }
}

void Scene::debug(string message)
{
  this->debug_msg = message;
}