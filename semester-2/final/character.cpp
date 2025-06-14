#include <curses.h>
#include "character.h"
#include "scene.h"
#include <vector>
#include <algorithm>

using std::copy_if, std::back_inserter, std::find;

bool is_walkable(Tile t, bool has_key)
{
  return t == Tile::CORRIDOR || t == Tile::KEY || t == Tile::LADDER || (has_key && t == Tile::CAGE);
}

Character::Character(Scene &scene, char symbol) : scene(scene), symbol(symbol)
{
  this->is_trapped = false;
  this->has_key = false;
  this->set_random_position();
}

vector<TileWithDirection> Character::look_around()
{
  vector<TileWithDirection> around;
  int x = this->position.x, y = this->position.y;

  around.push_back({this->scene.get_tile(x, y - 1), {0, -1}}); // TOP
  around.push_back({this->scene.get_tile(x, y + 1), {0, 1}});  // BOTTOM
  around.push_back({this->scene.get_tile(x - 1, y), {-1, 0}}); // LEFT
  around.push_back({this->scene.get_tile(x + 1, y), {1, 0}});  // RIGHT

  around.push_back({this->scene.get_tile(x + 1, y - 1), {1, -1}});  // TOP-RIGHT
  around.push_back({this->scene.get_tile(x - 1, y + 1), {-1, 1}});  // BOTTOM-LEFT
  around.push_back({this->scene.get_tile(x - 1, y - 1), {-1, -1}}); // TOP-LEFT
  around.push_back({this->scene.get_tile(x + 1, y + 1), {1, 1}});   // BOTTOM-RIGHT

  vector<TileWithDirection> valid_around;
  bool has_key = this->has_key;
  copy_if(around.begin(), around.end(), back_inserter(valid_around), [](TileWithDirection &t, bool has_key)
          { return is_walkable(t.tile, has_key); });

  return valid_around;
}

void Character::render()
{
  mvaddch(this->position.y, this->position.x, this->is_trapped ? static_cast<char>(Tile::CAGE) : this->symbol);
}

const Point Character::get_position() const
{
  return this->position;
}

void Character::set_random_position()
{
  Dimensions dimensions = this->scene.get_dimensions();

  Point tmp_pos = {0, 0};
  while (scene.get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR)
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

  vector<TileWithDirection> around = this->look_around();
  if (around.empty())
  {
    this->is_trapped = true;
    return;
  }

  for (TileWithDirection &t : around)
  {
    // Todo: make it remember where the key was
    if (!this->has_key && t.tile == Tile::KEY)
    {
      this->has_key = true;
      this->position.x += t.direction.x;
      this->position.y += t.direction.y;
      this->direction = t.direction;
      this->visited.insert({this->position.x, this->position.y});
      return;
    }

    if (t.direction == this->direction)
    {
      Point new_pos = {this->position.x + t.direction.x, this->position.y + t.direction.y};
      if (this->visited.find(new_pos) == this->visited.end())
      {
        this->position = new_pos;
        this->direction = t.direction;
        this->visited.insert(new_pos);
        return;
      }
    }
  }

  vector<TileWithDirection> non_visited;
  copy_if(around.begin(), around.end(), back_inserter(non_visited), [this](TileWithDirection &t)
          {
    Point new_pos = {this->position.x + t.direction.x, this->position.y + t.direction.y};
    return this->visited.find(new_pos) == this->visited.end(); });

  if (non_visited.empty())
  {
    int random_index = random() % around.size();
    this->position.x += around[random_index].direction.x;
    this->position.y += around[random_index].direction.y;
    this->direction = around[random_index].direction;
    this->visited.insert({this->position.x, this->position.y});
  }
  else
  {
    int random_index = random() % non_visited.size();
    this->position.x += non_visited[random_index].direction.x;
    this->position.y += non_visited[random_index].direction.y;
    this->direction = non_visited[random_index].direction;
    this->visited.insert({this->position.x, this->position.y});
  }

  if (this->scene.get_tile(this->position.x, this->position.y) == Tile::TRAP)
  {
    this->is_trapped = true;
  }
}

void Character::move_to(int x, int y)
{
  // TODO: implement
}