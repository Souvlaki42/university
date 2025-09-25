#ifndef CHARACTER
#define CHARACTER

#include "utils.h"
#include <vector>
#include <map>
#include <string>

class Character
{
private:
  Point position;
  Point direction;
  Point cage_position;
  Point key_position;
  int state;
  char symbol;
  int trapped;
  int has_key;
  class Scene &scene;
  std::map<std::string, int> visited_counts;
  std::map<std::string, int> unreachable_points;

  bool is_walkable(int t);
  std::vector<std::pair<Point, int>> look_around_from(Point from);
  std::string key_for_point(Point p);

public:
  Character(Scene &scene, char symbol, int has_key, Point position = {-1, -1});

  void render();
  void update(Character &partner);
  void move();
  void move(Point target_pos);

  Point get_position();
  void set_position();
  void set_position(Point new_pos);

  bool is_trapped();
  void set_trapped(int trapped);

  int get_has_key();
  void set_has_key(int status);
  int get_state();
  void set_state(int new_state);
};

#endif