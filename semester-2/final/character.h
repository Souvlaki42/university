#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <set>
#include <vector>
#include <unordered_map>

using std::set, std::vector, std::unordered_map;

class Character
{
private:
  Point position;
  Point direction;
  Point cage_position;
  Point key_position;
  CharacterState state;
  char symbol;
  bool trapped, has_key;
  class Scene &scene;
  set<Point> visited;

  const bool is_walkable(const Tile t) const;
  void move(const Point &target_pos = {-1, -1});

public:
  unordered_map<Point, Tile> look_around_from(Point from);
  Character(class Scene &scene, char symbol, bool has_key = false, Point position = {-1, -1});

  void update(Character &partner);
  void render();

  const Point get_position() const;
  void set_position(const Point &new_pos = Point{-1, -1});

  const bool is_trapped() const;
  void set_trapped(const bool trapped);
};

#endif