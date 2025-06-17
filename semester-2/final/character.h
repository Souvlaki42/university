#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <set>
#include <vector>
#include <map>
#include <queue>

using std::set, std::vector;

class Character
{
private:
  Point position;
  Point direction;
  Point trap_position;
  Point key_position;

  char symbol;
  bool is_trapped, has_key;
  class Scene &scene;
  const vector<TileWithDirection> look_around_from(Point from) const;
  set<Point> visited;

public:
  Character(class Scene &scene, char symbol);
  void move();
  void move_to(int x, int y);
  void render();
  const Point get_position() const;
  void set_random_position();
};

#endif