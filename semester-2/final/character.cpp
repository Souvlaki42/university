#include <cursesw.h>
#include "character.h"
#include "scene.h"

using std::vector, std::set;

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

  this->scene.log(make_char_key(L"Θέση", this->symbol), this->position);
  this->scene.log(make_char_key(L"Κατεύθηνση", this->symbol), this->direction);
  this->scene.log(make_char_key(L"Είναι παγιδευμένος", this->symbol), this->trapped);
  this->scene.log(make_char_key(L"Έχει κλειδί", this->symbol), this->has_key);
  this->scene.log(make_char_key(L"Κατάσταση", this->symbol), this->state);
  this->scene.log(make_char_key(L"Θέση κλειδιού", this->symbol), this->key_position);
  this->scene.log(make_char_key(L"Θέση κλουβιού", this->symbol), this->cage_position);
}

unordered_map<Point, Tile> Character::look_around_from(Point from)
{
  vector<Point> directions;
  unordered_map<Point, Tile> around;

  directions.push_back({0, -1});  // Πάνω
  directions.push_back({0, 1});   // Κάτω
  directions.push_back({-1, 0});  // Αριστερά
  directions.push_back({1, 0});   // Δεξιά
  directions.push_back({1, -1});  // Πάνω δεξιά
  directions.push_back({-1, 1});  // Κάτω αριστερά
  directions.push_back({-1, -1}); // Πάνω αριστερά
  directions.push_back({1, 1});   // Κάτω δεξιά

  for (int i = 0; i < directions.size(); i++)
  {
    Point dir = directions[i];
    around.insert({dir, this->scene.get_tile(from.x + dir.x, from.y + dir.y)});
  }

  return around;
}

void Character::render()
{
  mvaddch(this->position.y, this->position.x, this->trapped ? tile_to_char(Tile::CAGE) : this->symbol);
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
    this->visited.insert(new_pos);
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
      throw std::runtime_error("Δεν βρέθηκαν διάδρομοι για την τοποθέτηση τών χαρακτήρων.");
    }
  } while (this->scene.get_tile(tmp_pos.x, tmp_pos.y) != Tile::CORRIDOR);

  this->position = tmp_pos;
  this->visited.insert(tmp_pos);
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
}

void Character::update(Character &partner)
{
  this->scene.log(make_char_key(L"Θέση", this->symbol), this->position);
  this->scene.log(make_char_key(L"Κατεύθηνση", this->symbol), this->direction);
  this->scene.log(make_char_key(L"Είναι παγιδευμένος", this->symbol), this->trapped);
  this->scene.log(make_char_key(L"Έχει κλειδί", this->symbol), this->has_key);
  this->scene.log(make_char_key(L"Κατάσταση", this->symbol), this->state);
  this->scene.log(make_char_key(L"Θέση κλειδιού", this->symbol), this->key_position);
  this->scene.log(make_char_key(L"Θέση κλουβιού", this->symbol), this->cage_position);
}

void Character::move(const Point &target_pos)
{
}