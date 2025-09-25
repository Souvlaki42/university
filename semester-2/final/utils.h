#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define MAX_MOVES 1000         // Πόσα τέρμινα είναι αποδέκτο να περάσουν πριν η προσομοίωση τελειώσει
#define FRAME_DELAY_MS 1000000 // Ο χρόνος μεταξύ δύο τέρμινων σε μικροδευτερόλεπτα (1 δευτερόλεπτο)

struct Point
{
  int x;
  int y;
};

#define TILE_NONE 0
#define TILE_WALL 1
#define TILE_CORRIDOR 2
#define TILE_LADDER 3
#define TILE_KEY 4
#define TILE_TRAP 5
#define TILE_CAGE 6

#define STATE_EXPLORING 0
#define STATE_FETCHING_KEY 1
#define STATE_GOING_TO_CAGE 2
#define STATE_GOING_TO_LADDER 3
#define STATE_IDLE 4

#define GAME_RUNNING 0
#define GAME_WINNING 1
#define GAME_LOSING 2
#define GAME_DONE 3

char tile_to_char(int t);
int char_to_tile(char c);

#endif