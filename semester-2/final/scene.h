#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "utils.h"

class Character;

class Scene
{
public:
  Scene(const std::string &map_path);

  void render();
  void place_characters(Character &char1, Character &char2);
  void remove_obstacles();

  const Tile get_tile(int x, int y) const;
  void set_tile(int x, int y, const Tile &newTile);
  const Dimensions get_dimensions() const;
  const Point get_ladder_position() const;

  template <typename T>
  void log(const std::wstring &key, const T &value);
  void log_event(const std::wstring &event);

private:
  std::vector<std::vector<Tile>> contents;
  Dimensions dimensions;
  Point ladder_pos;

  std::map<std::wstring, std::wstring> debug_status;
  std::vector<std::wstring> event_logs;
  static const size_t MAX_EVENT_LOGS = 5;

  void loadFromText(const std::string &path);
  void loadFromBinary(const std::string &path);
  void placeTileAtRandomCorridor(Tile tileToPlace);
  void draw_general_stats_panel();
  void draw_character_stats_panel();
};

#endif