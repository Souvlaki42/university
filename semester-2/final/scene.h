#ifndef MAP
#define MAP

#include <vector>
#include <map>
#include <sstream>
#include "utils.h"
#include "character.h"

using std::vector, std::map, std::wstringstream, std::wstring, std::string;

class Scene
{
private:
  vector<vector<Tile>> contents;
  Dimensions dimensions;
  Point ladder_pos;
  int moves;
  bool winning;
  bool running;
  vector<wstring> event_logs;
  map<wstring, wstring> debug_status;

  void loadFromText(const string &path);
  void loadFromBinary(const string &path);
  void placeInitialItems();
  void placeTileAtRandomCorridor(Tile tileToPlace);
  void draw_general_stats_panel();
  void draw_character_stats_panel();
  const vector<wstring> &get_event_logs() const;
  const map<wstring, wstring> &get_debug_status() const;

public:
  Scene(const string &map_path);
  ~Scene();

  const bool is_winning() const;
  const bool is_running() const;

  void update();
  void render();
  void clear_maze(const Point &player1_pos, const Point &player2_pos);
  void place_characters(Character &char1, Character &char2);
  void stop_running();

  template <typename... Args>
  void log(const wstring &key, const Args &...args)
  {
    wstringstream buffer;

    buffer << std::boolalpha;

    (buffer << ... << args);

    if (key.empty())
    {
      this->event_logs.push_back(buffer.str());
      if (this->event_logs.size() > 20)
      {
        this->event_logs.erase(this->event_logs.begin());
      }
    }
    else
    {
      this->debug_status[key] = buffer.str();
    }
  }

  const Dimensions get_dimensions() const;
  const Tile get_tile(int x, int y) const;
  const Point get_ladder_position() const;

  void set_tile(int x, int y, const Tile &newTile);
  void set_winning(const bool winning);
};

#endif