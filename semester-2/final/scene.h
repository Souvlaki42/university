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
  void remove_obstacles(const Point &player1_pos, const Point &player2_pos);

  Tile get_tile(int x, int y) const;
  void set_tile(int x, int y, const Tile &newTile);
  const Dimensions get_dimensions() const;
  const Point get_ladder_position() const;

private:
  std::vector<std::vector<Tile>> contents;
  Dimensions dimensions;
  Point ladder_pos;

  std::map<std::string, std::string> debug_status;
  std::vector<std::string> event_logs;
  static const size_t MAX_EVENT_LOGS = 5;

  void loadFromText(const std::string &path);
  void loadFromBinary(const std::string &path);
  void placeTileAtRandomCorridor(Tile tileToPlace);
};

#endif