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

Character::Character(Scene &scene, char symbol) : scene(scene), symbol(symbol), is_trapped(false), has_key(false), state(State::EXPLORING)
{
  this->key_position = {-1, -1};
  this->cage_position = {-1, -1};
  this->set_random_position();
}

const vector<TileWithDirection> Character::look_around_from(Point from) const
{
  vector<TileWithDirection> around;

  around.push_back({this->scene.get_tile(from.x, from.y - 1), {0, -1}});
  around.push_back({this->scene.get_tile(from.x, from.y + 1), {0, 1}});
  around.push_back({this->scene.get_tile(from.x - 1, from.y), {-1, 0}});
  around.push_back({this->scene.get_tile(from.x + 1, from.y), {1, 0}});

  around.push_back({this->scene.get_tile(from.x + 1, from.y - 1), {1, -1}});
  around.push_back({this->scene.get_tile(from.x - 1, from.y + 1), {-1, 1}});
  around.push_back({this->scene.get_tile(from.x - 1, from.y - 1), {-1, -1}});
  around.push_back({this->scene.get_tile(from.x + 1, from.y + 1), {1, 1}});

  vector<TileWithDirection> valid_around;
  copy_if(around.begin(), around.end(), back_inserter(valid_around),
          [this](TileWithDirection &t)
          { return is_walkable(t.tile, this->has_key); });

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

void Character::update()
{
  if (this->scene.get_state() == GameState::WINNING)
  {
    Point ladder_pos = this->scene.get_ladder_position();
    this->move_to(ladder_pos.x, ladder_pos.y);
    if (this->position == ladder_pos)
    {
      this->scene.set_state(GameState::DONE);
    }
  }

  if (this->state == State::FETCHING_KEY)
  {
    this->move_to(this->key_position.x, this->key_position.y);
    if (this->has_key)
    {
      this->state = State::GOING_TO_CAGE;
    }
    return;
  }

  if (this->state == State::GOING_TO_CAGE)
  {
    this->move_to(this->cage_position.x, this->cage_position.y);
    if (this->position == this->cage_position)
    {
      this->scene.set_state(GameState::WINNING);
      this->state = State::EXPLORING;
    }
    return;
  }

  this->move();
}

void Character::move()
{
  if (this->is_trapped)
    return;

  vector<TileWithDirection> around = this->look_around_from(this->position);
  if (around.empty())
  {
    return;
  }

  for (TileWithDirection &t : around)
  {
    if (t.tile == Tile::KEY)
    {
      this->key_position = this->position + t.direction;
      Point new_direction = t.direction;
      double option = double(random()) / RAND_MAX;
      if (option <= 0.5)
        new_direction = Point{-t.direction.x, -t.direction.y};
      else
      {
        try
        {
          this->has_key = true;
          this->scene.set_tile(this->key_position.x, this->key_position.y, Tile::CORRIDOR);
        }
        catch (const std::exception &e)
        {
          this->scene.debug(e.what());
        }
      }
      this->position.x += new_direction.x;
      this->position.y += new_direction.y;
      this->direction = new_direction;
      this->visited.insert({this->position.x, this->position.y});
      return;
    }

    if (t.tile == Tile::CAGE)
    {
      this->cage_position = this->position + t.direction;
      if (has_key)
      {
        this->position.x += t.direction.x;
        this->position.y += t.direction.y;
        this->direction = t.direction;
        this->visited.insert({this->position.x, this->position.y});
        this->scene.set_state(GameState::WINNING);
      }
      else if (key_position != Point{-1, -1})
      {
        this->state == State::FETCHING_KEY;
        return;
      }
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
    try
    {
      this->is_trapped = true;
      this->scene.set_tile(this->position.x, this->position.y, Tile::CAGE);
      if (this->has_key)
      {
        this->scene.set_state(GameState::LOSING);
      }
    }
    catch (const std::out_of_range &e)
    {
      this->is_trapped = false;
      this->scene.debug(e.what());
    }
  }
}

void Character::move_to(int target_x, int target_y)
{
  Point start = this->position;
  Point goal = {target_x, target_y};

  if (start == goal)
    return;

  std::queue<Point> frontier;
  std::map<Point, Point> came_from;
  std::set<Point> visited_bfs;

  frontier.push(start);
  visited_bfs.insert(start);

  while (!frontier.empty())
  {
    Point current = frontier.front();
    frontier.pop();

    if (current == goal)
      break;

    for (const auto &next : this->look_around_from(current))
    {
      Point neighbor = {current.x + next.direction.x, current.y + next.direction.y};
      if (visited_bfs.find(neighbor) == visited_bfs.end())
      {
        frontier.push(neighbor);
        visited_bfs.insert(neighbor);
        came_from[neighbor] = current;
      }
    }
  }

  if (came_from.find(goal) == came_from.end())
    return; // No path found

  std::vector<Point> path;
  Point current = goal;
  while (current != start)
  {
    path.push_back(current);
    current = came_from.at(current);
  }
  std::reverse(path.begin(), path.end());

  if (!path.empty())
  {
    Point next_step = path.front();
    this->direction = {next_step.x - this->position.x, next_step.y - this->position.y};
    this->position = next_step;
    this->visited.insert(next_step);

    // After moving, correctly process the tile the character landed on.
    Tile landed_tile = this->scene.get_tile(next_step.x, next_step.y);
    if (landed_tile == Tile::KEY)
    {
      this->has_key = true;
      // Erase the key from the map so it can't be picked up again
      this->scene.set_tile(this->position.x, this->position.y, Tile::CORRIDOR);
    }
    else if (landed_tile == Tile::TRAP)
    {
      try
      {
        this->is_trapped = true;
        this->scene.set_tile(this->position.x, this->position.y, Tile::CAGE);
      }
      catch (const std::out_of_range &e)
      {
        this->is_trapped = false;
        this->scene.debug(e.what());
      }
    }
  }
}