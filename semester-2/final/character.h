#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <set>
#include <vector>
#include <map>
#include <queue>

using std::set, std::vector;

enum class State
{
  EXPLORING,
  FETCHING_KEY,
  GOING_TO_CAGE
};
class Character
{
private:
  Point position;
  Point direction;
  Point cage_position;
  Point key_position;
  State state;

  char symbol;
  bool is_trapped, has_key;
  class Scene &scene;
  const vector<TileWithDirection> look_around_from(Point from) const;
  void move();
  void move_to(int x, int y);
  set<Point> visited;

public:
  Character(class Scene &scene, char symbol);
  void update();
  void render();
  const Point get_position() const;
  void set_random_position();
};

#endif