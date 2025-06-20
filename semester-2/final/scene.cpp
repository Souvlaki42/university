#include <iostream>
#include <vector>
#include <fstream>
#include <cursesw.h>

#include "character.h"
#include "scene.h"

#define TERMINA 1000

using std::cout, std::vector, std::string, std::ifstream, std::out_of_range;

Scene::Scene(const std::string &map_path) : moves(0), running(true), winning(false)
{
  this->log(L"Κινήσεις", this->moves);
  if (map_path.size() > 4 && map_path.substr(map_path.size() - 4) == ".dat")
  {
    this->loadFromBinary(map_path);
  }
  else
  {
    this->loadFromText(map_path);
  }

  this->placeInitialItems();
}

void Scene::loadFromText(const std::string &path)
{
  std::ifstream file(path);
  if (!file)
  {
    throw std::runtime_error("Αδυναμία ανοίγματος αρχείου χάρτη " + path);
  }

  std::string line;
  size_t map_width = 0;
  size_t y_coord = 0;

  while (getline(file, line))
  {
    if (map_width == 0 && !line.empty())
    {
      map_width = line.length();
    }

    std::vector<Tile> row;
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
    throw std::runtime_error("Ο χάρτης είναι κενός ή μη έγκυρος.");
  }
}

void Scene::loadFromBinary(const std::string &path)
{
  std::ifstream file(path, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Αδυναμία ανοίγματος δυαδικού αρχείου χάρτη " + path);
  }

  uint32_t width = 0, height = 0;
  file.read(reinterpret_cast<char *>(&width), sizeof(width));
  file.read(reinterpret_cast<char *>(&height), sizeof(height));

  if (!file)
  {
    throw std::runtime_error("Μη έγκυρη ή κατεστραμμένη κεφαλίδα στο δυαδικό αρχείο " + path);
  }

  this->dimensions = {width, height};

  if (this->dimensions.width <= 0 || this->dimensions.height <= 0)
  {
    throw std::runtime_error("Ο χάρτης είναι κενός ή μη έγκυρος.");
  }

  this->contents.resize(height, std::vector<Tile>(width));

  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      char tile_char;
      file.read(&tile_char, sizeof(tile_char));
      if (!file)
      {
        throw std::runtime_error("Ελλιπή δεδομένα χάρτη στο αρχείο " + path);
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
    if (safety_counter > 10000)
    {
      throw std::runtime_error("Δεν βρέθηκαν διάδρομοι για την τοποθέτηση των αντικειμένων.");
    }
  } while (get_tile(random_pos.x, random_pos.y) != Tile::CORRIDOR);

  set_tile(random_pos.x, random_pos.y, tileToPlace);
}

void Scene::placeInitialItems()
{
  placeTileAtRandomCorridor(Tile::TRAP);
  placeTileAtRandomCorridor(Tile::TRAP);
  placeTileAtRandomCorridor(Tile::KEY);
}

Scene::~Scene()
{
  if (this->is_winning())
  {
    cout << "Τελικά βρεθήκαν οι χαρακτήρες και το βασίλειο σώθηκε. Πέρασαν " << this->moves << " τέρμινα.\n";
  }
  else
  {
    cout << "Τελικά δεν βρεθήκαν οι χαρακτήρες και το βασίλειο χάθηκε. Πέρασαν " << this->moves << " τέρμινα.\n";
  }
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
  this->log(L"Κινήσεις", this->moves);
  if (getch() == 'q' || this->moves >= TERMINA)
  {
    this->set_winning(false);
    this->stop_running();
  }
}

void Scene::render()
{
  box(stdscr, 0, 0);
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y + 1, x + 1, tile_to_char(this->contents[y][x]));
    }
  }

  this->draw_debug();
}

void Scene::draw_debug()
{
  int screen_height, screen_width;
  getmaxyx(stdscr, screen_height, screen_width);

  const int panel_start_x = this->dimensions.width + 2;
  const int panel_width = screen_width - panel_start_x;
  const int text_padding = 2;

  const int max_text_width = (panel_width > text_padding * 2) ? (panel_width - text_padding * 2) : 0;

  for (int y = 1; y < this->dimensions.height - 1; ++y)
  {
    move(y, panel_start_x + 1);
    clrtoeol();
  }

  mvvline(1, panel_start_x, ACS_VLINE, this->dimensions.height);

  int current_y = 2;
  if (max_text_width > 0)
  {
    mvaddwstr(current_y++, panel_start_x + text_padding, L"--- ΚΑΤΑΣΤΑΣΗ ---");
    current_y++;

    const std::map<std::wstring, std::wstring> &status = this->get_debug_status();
    for (std::map<std::wstring, std::wstring>::const_iterator it = status.begin(); it != status.end(); ++it)
    {
      if (current_y >= this->dimensions.height - 2)
        break;

      std::wstring line = it->first + L": " + it->second;
      if (line.length() > max_text_width)
      {
        line = line.substr(0, max_text_width);
      }
      mvaddwstr(current_y++, panel_start_x + text_padding, line.c_str());
    }

    current_y += 2;
    mvaddwstr(current_y++, panel_start_x + text_padding, L"--- ΣΥΜΒΑΝΤΑ ---");

    const std::vector<std::wstring> &events = this->get_event_logs();
    for (size_t i = 0; i < events.size(); ++i)
    {
      if (current_y >= this->dimensions.height - 2)
        break;

      std::wstring line = events[i];
      if (line.length() > max_text_width)
      {
        line = line.substr(0, max_text_width);
      }
      mvaddwstr(current_y++, panel_start_x + text_padding, line.c_str());
    }
  }
}

const std::vector<std::wstring> &Scene::get_event_logs() const
{
  return this->event_logs;
}

const std::map<std::wstring, std::wstring> &Scene::get_debug_status() const
{
  return this->debug_status;
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
    this->contents[y][x] = Tile::NONE;
  }
  this->contents[y][x] = newTile;
}

void Scene::set_winning(const bool winning)
{
  this->winning = winning;
}

void Scene::stop_running()
{
  this->running = false;
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

void Scene::clear_maze(const Point &player1_pos, const Point &player2_pos)
{
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      Point current_pos = {(int)(x), (int)(y)};

      if (current_pos == player1_pos || current_pos == player2_pos)
      {
        continue;
      }

      const Tile tile = this->get_tile(x, y);
      if (tile == Tile::CAGE || tile == Tile::TRAP || tile == Tile::WALL)
      {
        this->set_tile(x, y, Tile::CORRIDOR);
      }
    }
  }
}