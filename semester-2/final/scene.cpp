#include <iostream>
#include <vector>
#include <fstream>
#include <cursesw.h>
#include <sstream>

#include "character.h"
#include "scene.h"

using std::map, std::vector, std::string, std::ifstream, std::out_of_range, std::exception, std::wstring, std::runtime_error, std::ios, std::max, std::pair, std::wstringstream, std::boolalpha;

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
  box(stdscr, 0, 0);
  for (size_t y = 0; y < this->contents.size(); ++y)
  {
    for (size_t x = 0; x < this->contents[y].size(); ++x)
    {
      mvaddch(y + 1, x + 1, tile_to_char(this->contents[y][x]));
    }
  }

  this->draw_general_stats_panel();
  this->draw_character_stats_panel();
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
  this->log_event(L"Οι τοίχοι και οι παγίδες εξαφανίστηκαν!");
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

void Scene::log_event(const wstring &event)
{
  this->event_logs.insert(this->event_logs.begin(), event);
  if (this->event_logs.size() > MAX_EVENT_LOGS)
  {
    this->event_logs.pop_back();
  }
}

template <typename T>
void Scene::log(const wstring &key, const T &value)
{
  wstringstream wss;
  wss << boolalpha;
  wss << value;
  this->debug_status[key] = wss.str();
}

template void Scene::log<int>(const wstring &, const int &);
template void Scene::log<bool>(const wstring &, const bool &);
template void Scene::log<Point>(const wstring &, const Point &);
template void Scene::log<CharacterState>(const wstring &, const CharacterState &);
template void Scene::log<wstring>(const wstring &, const wstring &);
template void Scene::log<GameState>(const wstring &, const GameState &);

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

void Scene::draw_general_stats_panel()
{
  int screen_height, screen_width;
  getmaxyx(stdscr, screen_height, screen_width);

  const int panel_start_x = this->dimensions.width + 1;
  const int panel_width = screen_width - panel_start_x;
  const int text_padding = 2;
  const int max_text_width = (panel_width > text_padding * 2) ? (panel_width - text_padding * 2) : 0;
  int current_y = 2;

  for (int y = 1; y < this->dimensions.height; ++y)
  {
    move(y, panel_start_x + 1);
    clrtoeol();
  }

  mvvline(1, panel_start_x, ACS_VLINE, this->dimensions.height);

  if (max_text_width <= 0)
    return;

  mvaddwstr(current_y++, panel_start_x + text_padding, L"--- ΓΕΝΙΚΑ ---");
  current_y++;

  const map<wstring, wstring> &status = this->debug_status;
  for (map<wstring, wstring>::const_iterator it = status.begin(); it != status.end(); ++it)
  {
    if (it->first.find(L'(') == wstring::npos)
    {
      if (current_y >= this->dimensions.height - 1)
        break;

      wstring line = it->first + L": " + it->second;
      if (line.length() > max_text_width)
      {
        line = line.substr(0, max_text_width);
      }
      mvaddwstr(current_y++, panel_start_x + text_padding, line.c_str());
    }
  }

  current_y++;
  if (current_y >= screen_height - 1)
    return;
  mvaddwstr(current_y++, panel_start_x + text_padding, L"--- ΣΥΜΒΑΝΤΑ ---");

  const vector<wstring> &events = this->event_logs;
  const int max_event_width = screen_width - text_padding * 2;
  for (const wstring &event_line : events)
  {
    if (current_y >= screen_height - 1)
      break;
    wstring line = event_line;
    if (line.length() > max_event_width)
      line = line.substr(0, max_event_width);
    mvaddwstr(current_y++, panel_start_x + text_padding, line.c_str());
  }
}

void Scene::draw_character_stats_panel()
{
  int screen_height, screen_width;
  getmaxyx(stdscr, screen_height, screen_width);

  int panel_start_y = this->dimensions.height + 2;
  const int text_padding = 2;
  int current_y = panel_start_y;

  for (int y = panel_start_y - 1; y < screen_height; ++y)
  {
    move(y, 1);
    clrtoeol();
  }

  mvhline(panel_start_y - 1, 1, ACS_HLINE, screen_width - 2);

  if (current_y >= screen_height)
    return;

  const map<wstring, wstring> &all_status = this->debug_status;
  vector<wstring> grigorakis_stats;
  vector<wstring> asimenia_stats;

  for (const pair<const wstring, wstring> &pair : all_status)
  {
    const wstring &key = pair.first;
    const wstring &val = pair.second;

    if (key.find(L"(G)") != wstring::npos)
    {
      grigorakis_stats.push_back(key + L": " + val);
    }
    else if (key.find(L"(S)") != wstring::npos)
    {
      asimenia_stats.push_back(key + L": " + val);
    }
  }

  mvaddwstr(current_y++, text_padding, L"--- ΧΑΡΑΚΤΗΡΕΣ ---");
  current_y++;

  const int col_width = (screen_width / 2) - text_padding;
  const int x_col1 = text_padding;
  const int x_col2 = (screen_width / 2) + text_padding / 2;
  size_t max_rows = max(grigorakis_stats.size(), asimenia_stats.size());

  for (size_t i = 0; i < max_rows; ++i)
  {
    if (current_y >= screen_height - 1)
      break;
    if (i < grigorakis_stats.size())
    {
      wstring line = grigorakis_stats[i];
      if (line.length() > col_width)
        line = line.substr(0, col_width);
      mvaddwstr(current_y, x_col1, line.c_str());
    }
    if (i < asimenia_stats.size())
    {
      wstring line = asimenia_stats[i];
      if (line.length() > col_width)
        line = line.substr(0, col_width);
      mvaddwstr(current_y, x_col2, line.c_str());
    }
    current_y++;
  }
}