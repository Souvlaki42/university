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
  int moves;

public:
  Scene(const char *map_path);
  ~Scene();

  const bool is_open() const;
  const bool is_game_over(const char ch) const;
  void render();
  void increment_moves();

  const Dimensions get_dimensions() const;
  const Tile get_tile(int x, int y) const;
  void set_tile(int x, int y, const Tile &newTile);
};

#endif