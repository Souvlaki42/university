#include "utils.h"

char tile_to_char(int t)
{
  if (t == TILE_WALL)
    return '*';
  if (t == TILE_CORRIDOR)
    return ' ';
  if (t == TILE_LADDER)
    return 'L';
  if (t == TILE_KEY)
    return 'K';
  if (t == TILE_TRAP)
    return 'T';
  if (t == TILE_CAGE)
    return 'C';
  return '0';
}

int char_to_tile(char c)
{
  if (c == '*')
    return TILE_WALL;
  if (c == ' ')
    return TILE_CORRIDOR;
  if (c == 'L')
    return TILE_LADDER;
  if (c == 'K')
    return TILE_KEY;
  if (c == 'T')
    return TILE_TRAP;
  if (c == 'C')
    return TILE_CAGE;
  return TILE_NONE;
}