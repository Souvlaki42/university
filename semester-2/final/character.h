#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <set>

using std::set;

class Character
{
private:
  Point position;
  char symbol;
  bool is_trapped, has_key;
  class Map &map;
  vector<TileWithPosition> look_around();
  set<Point> visited;

public:
  Character(class Map &map, char symbol);
  void move();
  void render();
  const Point get_position() const;
  void set_random_position();
};

#endif