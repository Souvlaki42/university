#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>
#include "utils.h"

class Character;

class Scene
{
public:
  Scene(std::string map_path);

  void render();
  void place_characters(Character &char1, Character &char2);
  void remove_obstacles(Point player1_pos, Point player2_pos);

  int get_tile(int x, int y);
  void set_tile(int x, int y, int newTile);
  Point get_dimensions();
  Point get_ladder_position();

private:
  std::vector<std::vector<int>> contents;
  Point dimensions;
  Point ladder_pos;

  void loadFromText(std::string path);
  void loadFromBinary(std::string path);
  void placeTileAtRandomCorridor(int tileToPlace);
};

#endif