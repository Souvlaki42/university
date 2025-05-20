#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <set>
#include <vector>

using std::set, std::vector;

class Character
{
private:
  Point position;
  Point direction;
  char symbol;
  bool is_trapped, has_key;
  class Scene &scene;
  vector<TileWithDirection> look_around();
  set<Point> visited;

public:
  Character(class Scene &scene, char symbol);
  void move_generic();
  void move_to(int x, int y);
  void render();
  const Point get_position() const;
  void set_random_position();
};

#endif