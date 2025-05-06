#include <curses.h>
#include "character.h"
#include "map.h"
#include <vector>
#include <algorithm>

using std::copy_if, std::back_inserter, std::find;

Character::Character(Map &map, char symbol) : map(map), symbol(symbol)
{
  this->is_trapped = false;
  this->has_key = false;
  this->set_random_position();
}

vector<TileWithPosition> Character::look_around()
{
  vector<TileWithPosition> around;
  int x = this->position.x, y = this->position.y;

  around.push_back({this->map.get_tile(x, y - 1), {x, y - 1}});         // TOP
  around.push_back({this->map.get_tile(x, y + 1), {x, y + 1}});         // BOTTOM
  around.push_back({this->map.get_tile(x - 1, y), {x - 1, y}});         // LEFT
  around.push_back({this->map.get_tile(x + 1, y), {x + 1, y}});         // RIGHT
  around.push_back({this->map.get_tile(x - 1, y - 1), {x - 1, y - 1}}); // TOP LEFT
  around.push_back({this->map.get_tile(x + 1, y - 1), {x + 1, y - 1}}); // TOP RIGHT
  around.push_back({this->map.get_tile(x - 1, y + 1), {x - 1, y + 1}}); // BOTTOM LEFT
  around.push_back({this->map.get_tile(x + 1, y + 1), {x + 1, y + 1}}); // BOTTOM RIGHT

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

  Point tmp_pos = {0, 0};
  while (map.get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR)
  {
    tmp_pos.x = random() % dimensions.width;
    tmp_pos.y = random() % dimensions.height;
  }

  this->position = tmp_pos;
}

void Character::move()
{
  if (this->is_trapped)
  {
    return;
  }

  vector<TileWithPosition> around = this->look_around();
  vector<TileWithPosition> valid_around, non_visited;
  copy_if(around.begin(), around.end(), back_inserter(valid_around), [](TileWithPosition &t)
          { return t.tile != Tile::NONE && t.tile != Tile::WALL; });
  for (TileWithPosition &t : valid_around)
  {
    if (this->visited.find(t.position) == this->visited.end())
    {
      copy_if(valid_around.begin(), valid_around.end(), back_inserter(non_visited), [this](TileWithPosition &t)
              { return visited.find(t.position) == visited.end(); });
      break;
    }
  }

  if (non_visited.size() == 0)
  {
    this->position = valid_around[random() % valid_around.size()].position;
  }
  else
  {
    for (size_t i = 0; i < non_visited.size(); ++i)
    {
      if (non_visited[i].tile == Tile::KEY)
      {
        this->has_key = true;
        this->position = non_visited[i].position;
        this->visited.insert(this->position);
        break;
      }
    }

    if (!this->has_key)
    {
      this->position = non_visited[random() % non_visited.size()].position;
    }
  }
}