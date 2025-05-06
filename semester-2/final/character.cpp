#include <curses.h>
#include "character.h"
#include "map.h"

Character::Character(Map &map, char symbol) : map(map), symbol(symbol)
{
  this->is_trapped = false;
  this->has_key = false;
  this->set_random_position();
}

Around Character::look_around()
{
  Around around;
  // around.top = this->map.get_tile(x, y - 1);
  // around.bottom = this->map.get_tile(x, y + 1);
  // around.left = this->map.get_tile(x - 1, y);
  // around.right = this->map.get_tile(x + 1, y);
  // around.top_left = this->map.get_tile(x - 1, y - 1);
  // around.top_right = this->map.get_tile(x + 1, y - 1);
  // around.bottom_left = this->map.get_tile(x - 1, y + 1);
  // around.bottom_right = this->map.get_tile(x + 1, y + 1);
  return around;
}

void Character::render()
{
  mvaddch(this->position.y, this->position.x, this->is_trapped ? 'C' : this->symbol);
}

const Point Character::get_position() const
{
  return this->position;
}

void Character::set_random_position()
{
  Dimensions dimensions = this->map.get_dimensions();

  Point tmp_random_position = {0, 0};
  while (map.get_tile(tmp_random_position) != Tile::CORRIDOR)
  {
    tmp_random_position.x = random() % dimensions.width;
    tmp_random_position.y = random() % dimensions.height;
  }

  this->position = tmp_random_position;
}

void Character::move()
{
  if (this->is_trapped)
  {
    return;
  }

  Around around = this->look_around();
}