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

public:
  Scene(const char *map_path);
  ~Scene();

  const bool is_open() const;
  void render();

  const Dimensions get_dimensions() const;
  const Tile get_tile(int x, int y) const;
};

#endif