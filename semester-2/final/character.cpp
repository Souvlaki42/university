#include <curses.h>
#include "character.h"
#include "scene.h"
#include <vector>
#include <string>
#include <cstdio>

using std::pair;
using std::vector;

Character::Character(Scene &scene, char symbol, int has_key, Point position) : scene(scene)
{
  this->position = position;
  this->direction = {1, 0};
  this->symbol = symbol;
  this->trapped = 0;
  this->has_key = has_key;
  this->state = STATE_EXPLORING;
  this->key_position = {-1, -1};
  this->cage_position = {-1, -1};
}

vector<pair<Point, int>> Character::look_around_from(Point from)
{
  vector<Point> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
  vector<pair<Point, int>> around;
  for (size_t i = 0; i < directions.size(); ++i)
  {
    Point dir = directions[i];
    around.push_back(pair<Point, int>(dir, this->scene.get_tile(from.x + dir.x, from.y + dir.y)));
  }
  return around;
}

void Character::render()
{
  mvaddch(this->position.y + 1, this->position.x + 1, this->trapped ? tile_to_char(TILE_CAGE) : this->symbol);
}

Point Character::get_position()
{
  return this->position;
}

void Character::set_position(Point new_pos)
{
  if (!(new_pos.x == -1 && new_pos.y == -1))
  {
    this->position = new_pos;
    this->visited_counts[key_for_point(new_pos)]++;
    return;
  }

  Point dimensions = this->scene.get_dimensions();
  Point tmp_pos = {0, 0};
  do
  {
    tmp_pos.x = random() % dimensions.x;
    tmp_pos.y = random() % dimensions.y;
  } while (this->scene.get_tile(tmp_pos.x, tmp_pos.y) != TILE_CORRIDOR);

  this->position = tmp_pos;
  this->visited_counts[key_for_point(tmp_pos)] = 1;
}

bool Character::is_trapped()
{
  return this->trapped;
}

bool Character::is_walkable(int t)
{
  return t == TILE_CORRIDOR || t == TILE_KEY || t == TILE_LADDER || t == TILE_TRAP || (this->has_key && t == TILE_CAGE);
}

void Character::set_trapped(int trapped)
{
  this->trapped = trapped;
  if (trapped)
    this->state = STATE_IDLE;
}

int Character::get_has_key() { return this->has_key; }
void Character::set_has_key(int status) { this->has_key = status; }
int Character::get_state() { return this->state; }
void Character::set_state(int new_state) { this->state = new_state; }

void Character::update(Character &partner)
{
  if (this->trapped)
  {
    this->state = STATE_IDLE;
    return;
  }

  vector<pair<Point, int>> surroundings = this->look_around_from(this->position);
  for (size_t i = 0; i < surroundings.size(); ++i)
  {
    Point rel = surroundings[i].first;
    int tile = surroundings[i].second;
    Point tile_abs_pos = {this->position.x + rel.x, this->position.y + rel.y};

    if (tile == TILE_KEY && this->key_position.x == -1 && this->key_position.y == -1)
    {
      this->key_position = tile_abs_pos;
    }
    else if (tile == TILE_CAGE && this->cage_position.x == -1 && this->cage_position.y == -1)
    {
      this->cage_position = tile_abs_pos;
    }
  }

  if (this->state == STATE_EXPLORING)
  {
    if (!(this->cage_position.x == -1 && this->cage_position.y == -1))
    {
      if (this->has_key && this->unreachable_points[key_for_point(this->cage_position)] == 0)
      {
        this->state = STATE_GOING_TO_CAGE;
      }
      else if (!(this->key_position.x == -1 && this->key_position.y == -1) && this->unreachable_points[key_for_point(this->key_position)] == 0)
      {
        this->state = STATE_FETCHING_KEY;
      }
    }
  }

  if (this->state == STATE_EXPLORING)
  {
    this->move();
  }
  else if (this->state == STATE_FETCHING_KEY)
  {
    this->move(this->key_position);
  }
  else if (this->state == STATE_GOING_TO_CAGE)
  {
    this->move(this->cage_position);
  }
  else if (this->state == STATE_GOING_TO_LADDER)
  {
    this->move(this->scene.get_ladder_position());
  }
}

void Character::move()
{
  Point p;
  p.x = -1;
  p.y = -1;
  this->move(p);
}

void Character::move(Point target_pos)
{
  Point next_pos = {-1, -1};
  int move_decided = 0;

  if (target_pos.x == -1 && target_pos.y == -1)
  {
    if (!move_decided)
    {
      Point straight_ahead_pos = {this->position.x + this->direction.x, this->position.y + this->direction.y};
      int tile_ahead = this->scene.get_tile(straight_ahead_pos.x, straight_ahead_pos.y);
      if (is_walkable(tile_ahead))
      {
        next_pos = straight_ahead_pos;
        move_decided = 1;
      }
    }

    if (!move_decided)
    {
      vector<Point> candidate_options;
      vector<pair<Point, int>> surroundings = this->look_around_from(this->position);
      for (size_t i = 0; i < surroundings.size(); ++i)
      {
        if (is_walkable(surroundings[i].second))
        {
          Point rel = surroundings[i].first;
          candidate_options.push_back({this->position.x + rel.x, this->position.y + rel.y});
        }
      }

      if (!candidate_options.empty())
      {
        int min_visits = -1;
        for (Point &pos : candidate_options)
        {
          int current_visits = this->visited_counts[key_for_point(pos)];
          if (min_visits == -1 || current_visits < min_visits)
          {
            min_visits = current_visits;
          }
        }

        vector<Point> least_visited_options;
        for (Point &pos : candidate_options)
        {
          if (this->visited_counts[key_for_point(pos)] == min_visits)
          {
            least_visited_options.push_back(pos);
          }
        }
        next_pos = least_visited_options[random() % least_visited_options.size()];
        move_decided = 1;
      }
    }
  }
  else
  {
    if (abs(target_pos.x - this->position.x) + abs(target_pos.y - this->position.y) == 1 && is_walkable(this->scene.get_tile(target_pos.x, target_pos.y)))
    {
      next_pos = target_pos;
      move_decided = 1;
    }
    if (!move_decided)
    {
      this->state = STATE_EXPLORING;
      return this->move();
    }
  }

  if (!(next_pos.x == -1 && next_pos.y == -1) && !(next_pos.x == this->position.x && next_pos.y == this->position.y))
  {
    this->direction = {next_pos.x - this->position.x, next_pos.y - this->position.y};
    this->set_position(next_pos);
  }
}

std::string Character::key_for_point(Point p)
{
  char buf[32];
  snprintf(buf, sizeof(buf), "%d,%d", p.x, p.y);
  return std::string(buf);
}