#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <unordered_map>
#include <unordered_set>

using std::unordered_map, std::unordered_set;

class Character
{
private:
  Point position;
  Point direction;
  Point cage_position;
  Point key_position;
  CharacterState state;
  char symbol;
  bool trapped;
  bool has_key;
  class Scene &scene;
  unordered_map<Point, int> visited_counts;
  unordered_set<Point> unreachable_points;

  void log_state();
  Point find_next_step(const Point &goal);
  const bool is_walkable(const Tile t) const;
  unordered_map<Point, Tile> look_around_from(Point from);

public:
  Character(Scene &scene, char symbol, bool has_key, Point position = {-1, -1});

  void render();
  void update(Character &partner);
  void move(const Point &target_pos = {-1, -1});

  const Point get_position() const;
  void set_position(const Point &new_pos = {-1, -1});

  const bool is_trapped() const;
  void set_trapped(const bool trapped);

  bool get_has_key() const;
  void set_has_key(bool status);
  CharacterState get_state() const;
  void set_state(CharacterState new_state);
};

#endif