#ifndef MAP
#define MAP

#include <vector>
#include <string>
#include <fstream>
#include "utils.h"

using std::vector, std::string, std::ifstream;

class Scene
{
private:
  ifstream file;
  vector<vector<Tile>> contents;
  Dimensions dimensions;
  Point ladder_pos;
  string debug_msg;
  int moves;
  GameState state;

public:
  Scene(const char *map_path);
  ~Scene();

  const bool is_open() const;
  const bool is_done() const;
  void update();
  void render();

  const Dimensions get_dimensions() const;
  const Tile get_tile(int x, int y) const;
  const Point get_ladder_position() const;
  void set_tile(int x, int y, const Tile &newTile);
  void debug(string message);
};

#endif