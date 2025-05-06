#ifndef MAP
#define MAP

#include <vector>
#include <string>
#include <fstream>
#include "utils.h"

using std::vector, std::string, std::ifstream;

class Map
{
private:
  ifstream file;
  vector<vector<Tile>> contents;
  Dimensions dimensions;

public:
  Map(const char *map_path);
  ~Map();

  const bool is_open() const;
  void render();

  const Dimensions get_dimensions() const;
  const Tile get_tile(int x, int y) const;
};

#endif