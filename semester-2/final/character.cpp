#include <cursesw.h>
#include "character.h"
#include "scene.h"
#include <queue>

using std::vector, std::queue, std::runtime_error, std::pair;

Character::Character(Scene &scene, char symbol, bool has_key, Point position) : scene(scene)
{
  this->position = position;
  this->direction = {1, 0};
  this->symbol = symbol;
  this->trapped = false;
  this->has_key = has_key;
  this->state = CharacterState::EXPLORING;
  this->key_position = {-1, -1};
  this->cage_position = {-1, -1};
  this->unreachable_points = {};
  this->log_state();
}

unordered_map<Point, Tile> Character::look_around_from(Point from)
{
  vector<Point> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};
  unordered_map<Point, Tile> around;

  for (const Point &dir : directions)
  {
    around.insert({dir, this->scene.get_tile(from.x + dir.x, from.y + dir.y)});
  }

  return around;
}

void Character::log_state()
{
  this->scene.log(make_char_key(L"Θέση", this->symbol), this->position);
  this->scene.log(make_char_key(L"Κατεύθηνση", this->symbol), this->direction);
  this->scene.log(make_char_key(L"Είναι παγιδευμένος", this->symbol), this->trapped);
  this->scene.log(make_char_key(L"Έχει κλειδί", this->symbol), this->has_key);
  this->scene.log(make_char_key(L"Κατάσταση", this->symbol), this->state);
  this->scene.log(make_char_key(L"Θέση κλειδιού", this->symbol), this->key_position);
  this->scene.log(make_char_key(L"Θέση κλουβιού", this->symbol), this->cage_position);
}

void Character::render()
{
  mvaddch(this->position.y + 1, this->position.x + 1, this->trapped ? tile_to_char(Tile::CAGE) : this->symbol);
}

const Point Character::get_position() const
{
  return this->position;
}

void Character::set_position(const Point &new_pos)
{
  if (new_pos != Point{-1, -1})
  {
    this->position = new_pos;
    this->visited_counts[new_pos]++;
    return;
  }

  Dimensions dimensions = this->scene.get_dimensions();
  Point tmp_pos = {0, 0};
  int safety_counter = 0;
  do
  {
    tmp_pos.x = random() % dimensions.width;
    tmp_pos.y = random() % dimensions.height;
    safety_counter++;
    if (safety_counter > MAX_RAND_PLACEMENTS)
    {
      throw runtime_error("Δεν βρέθηκαν διάδρομοι για την τοποθέτηση των χαρακτήρων.");
    }
  } while (this->scene.get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR);

  this->position = tmp_pos;
  this->visited_counts[tmp_pos] = 1;
}

const bool Character::is_trapped() const
{
  return this->trapped;
}

const bool Character::is_walkable(const Tile t) const
{
  return t == Tile::CORRIDOR || t == Tile::KEY || t == Tile::LADDER || t == Tile::TRAP || (this->has_key && t == Tile::CAGE);
}

void Character::set_trapped(const bool trapped)
{
  this->trapped = trapped;
  if (trapped)
    this->state = CharacterState::IDLE;
}

bool Character::get_has_key() const { return this->has_key; }
void Character::set_has_key(bool status) { this->has_key = status; }
CharacterState Character::get_state() const { return this->state; }
void Character::set_state(CharacterState new_state) { this->state = new_state; }

void Character::update(Character &partner)
{
  if (this->trapped)
  {
    this->state = CharacterState::IDLE;
    log_state();
    return;
  }

  unordered_map<Point, Tile> surroundings = this->look_around_from(this->position);
  for (const pair<Point, Tile> &pair : surroundings)
  {
    Point tile_abs_pos = {this->position.x + pair.first.x, this->position.y + pair.first.y};
    Tile tile = pair.second;

    if (tile == Tile::KEY && this->key_position == Point{-1, -1})
    {
      this->key_position = tile_abs_pos;
    }
    else if (tile == Tile::CAGE && this->cage_position == Point{-1, -1})
    {
      this->cage_position = tile_abs_pos;
    }
  }

  if (this->state == CharacterState::EXPLORING)
  {
    if (this->cage_position != Point{-1, -1})
    {
      if (this->has_key && this->unreachable_points.find(this->cage_position) == this->unreachable_points.end())
      {
        this->state = CharacterState::GOING_TO_CAGE;
      }
      else if (this->key_position != Point{-1, -1} && this->unreachable_points.find(this->key_position) == this->unreachable_points.end())
      {
        this->state = CharacterState::FETCHING_KEY;
      }
    }
  }

  switch (this->state)
  {
  case CharacterState::EXPLORING:
    this->move({-1, -1});
    break;
  case CharacterState::FETCHING_KEY:
    this->move(this->key_position);
    break;
  case CharacterState::GOING_TO_CAGE:
    this->move(this->cage_position);
    break;
  case CharacterState::GOING_TO_LADDER:
    this->move(this->scene.get_ladder_position());
    break;
  case CharacterState::IDLE:
    break;
  }

  log_state();
}

void Character::move(const Point &target_pos)
{
  Point next_pos = {-1, -1};
  bool move_decided = false;

  if (target_pos == Point{-1, -1})
  {
    if (this->key_position != Point{-1, -1} && !this->has_key)
    {
      if (abs(this->position.x - this->key_position.x) <= 1 && abs(this->position.y - this->key_position.y) <= 1)
      {
        if (random() % 2 == 0)
        {
          next_pos = this->key_position;
          move_decided = true;
          scene.log_event(L"Αποφάσισα να πάρω το κλειδί τώρα!");
        }
        else
        {
          scene.log_event(L"Αποφάσισα να αφήσω το κλειδί για αργότερα.");
          vector<Point> avoidance_options;
          unordered_map<Point, Tile> surroundings = this->look_around_from(this->position);
          for (const pair<Point, Tile> &pair : surroundings)
          {
            Point potential_pos = {this->position.x + pair.first.x, this->position.y + pair.first.y};
            if (is_walkable(pair.second) && potential_pos != this->key_position)
            {
              avoidance_options.push_back(potential_pos);
            }
          }

          if (!avoidance_options.empty())
          {
            next_pos = avoidance_options[random() % avoidance_options.size()];
            move_decided = true;
          }
        }
      }
    }

    if (!move_decided)
    {
      Point straight_ahead_pos = {this->position.x + this->direction.x, this->position.y + this->direction.y};
      Tile tile_ahead = this->scene.get_tile(straight_ahead_pos.x, straight_ahead_pos.y);
      if (is_walkable(tile_ahead))
      {
        next_pos = straight_ahead_pos;
        move_decided = true;
      }
    }

    if (!move_decided)
    {
      vector<Point> unvisited_options;
      unordered_map<Point, Tile> surroundings = this->look_around_from(this->position);
      for (const pair<Point, Tile> &pair : surroundings)
      {
        if (is_walkable(pair.second))
        {
          Point potential_pos = {this->position.x + pair.first.x, this->position.y + pair.first.y};
          if (this->visited_counts.find(potential_pos) == this->visited_counts.end())
          {
            unvisited_options.push_back(potential_pos);
          }
        }
      }
      if (!unvisited_options.empty())
      {
        next_pos = unvisited_options[random() % unvisited_options.size()];
        move_decided = true;
      }
    }

    if (!move_decided)
    {
      vector<Point> visited_options;
      unordered_map<Point, Tile> surroundings = this->look_around_from(this->position);
      for (const pair<Point, Tile> &pair : surroundings)
      {
        if (is_walkable(pair.second))
        {
          visited_options.push_back({this->position.x + pair.first.x, this->position.y + pair.first.y});
        }
      }

      if (!visited_options.empty())
      {
        int min_visits = -1;
        for (const Point &pos : visited_options)
        {
          int current_visits = this->visited_counts[pos];
          if (min_visits == -1 || current_visits < min_visits)
          {
            min_visits = current_visits;
          }
        }

        vector<Point> least_visited_options;
        for (const Point &pos : visited_options)
        {
          if (this->visited_counts[pos] == min_visits)
          {
            least_visited_options.push_back(pos);
          }
        }
        next_pos = least_visited_options[random() % least_visited_options.size()];
        move_decided = true;
      }
    }
  }
  else
  {
    next_pos = find_next_step(target_pos);
    if (next_pos == Point{-1, -1})
    {
      this->scene.log_event(L"Δεν βρέθηκε μονοπάτι, η εξερεύνηση συνεχίζεται.");
      this->unreachable_points.insert(target_pos);
      this->state = CharacterState::EXPLORING;
    }
  }

  if (next_pos != Point{-1, -1} && next_pos != this->position)
  {
    this->direction = {next_pos.x - this->position.x, next_pos.y - this->position.y};
    this->set_position(next_pos);
  }
}

Point Character::find_next_step(const Point &goal)
{
  if (this->position == goal)
    return this->position;

  queue<Point> q;
  q.push(this->position);

  unordered_map<Point, Point> came_from;
  came_from[this->position] = {-1, -1};

  while (!q.empty())
  {
    Point current = q.front();
    q.pop();

    if (current == goal)
    {
      Point step = goal;
      while (came_from.count(step) && came_from[step] != this->position)
      {
        step = came_from[step];
        if (step == Point{-1, -1})
          return {-1, -1};
      }
      return step;
    }

    unordered_map<Point, Tile> surroundings = this->look_around_from(current);
    for (const pair<Point, Tile> &pair : surroundings)
    {
      Point next = {current.x + pair.first.x, current.y + pair.first.y};
      if (is_walkable(pair.second) && came_from.find(next) == came_from.end())
      {
        q.push(next);
        came_from[next] = current;
      }
    }
  }

  return {-1, -1};
}