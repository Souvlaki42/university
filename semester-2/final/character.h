#ifndef CHARACTER
#define CHARACTER

#include "utils.h"

class Character
{
private:
  Point position;
  char symbol;
  bool is_trapped, has_key;
  class Map &map;
  Around look_around();

public:
  Character(class Map &map, char symbol);
  void move();
  void render();
  const Point get_position() const;
  void set_random_position();
};

#endif