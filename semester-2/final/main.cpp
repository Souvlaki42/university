#include <curses.h>
#include <unistd.h>
#include <string>
#include "scene.h"
#include "character.h"
#include "utils.h"
#include <time.h>

using std::string;

void process_character_move(Character &character, Character &partner, Scene &scene, int &gameState);
void check_game_over_conditions(Character &p1, Character &p2, Scene &scene, int &gameState, int &moves_left);
void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, int &gameState);

int main(int argc, char *argv[])
{
  srandom(time(NULL));

  if (argc < 2)
  {
    return 1;
  }

  std::string mapPath = argv[1];
  Scene scene = Scene(mapPath);
  Character grigorakis = Character(scene, 'G', 0);
  Character asimenia = Character(scene, 'S', 0);

  scene.place_characters(grigorakis, asimenia);

  int gameState = GAME_RUNNING;
  int moves_left = MAX_MOVES;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  timeout(0);

  scene.render();
  grigorakis.render();
  asimenia.render();
  refresh();

  usleep(FRAME_DELAY_MS);

  while (gameState != GAME_DONE)
  {
    if (getch() == 27)
    {
      break;
    }

    if (gameState == GAME_RUNNING || gameState == GAME_WINNING)
    {
      grigorakis.update(asimenia);
      process_character_move(grigorakis, asimenia, scene, gameState);

      if (gameState == GAME_RUNNING || gameState == GAME_WINNING)
      {
        asimenia.update(grigorakis);
        process_character_move(asimenia, grigorakis, scene, gameState);
      }

      moves_left--;

      check_game_over_conditions(grigorakis, asimenia, scene, gameState, moves_left);
    }

    erase();
    scene.render();
    grigorakis.render();
    asimenia.render();
    refresh();

    if (gameState == GAME_LOSING || (gameState == GAME_DONE && moves_left >= 0))
    {
      timeout(-1);
      getch();
      break;
    }

    usleep(FRAME_DELAY_MS);
  }

  endwin();

  return 0;
}

void process_character_move(Character &character, Character &partner, Scene &scene, int &gameState)
{
  if (gameState == GAME_LOSING || gameState == GAME_DONE)
    return;

  Point pos = character.get_position();
  int tile_at_pos = scene.get_tile(pos.x, pos.y);

  if (tile_at_pos == TILE_TRAP)
  {
    if (character.get_has_key())
    {
      gameState = GAME_LOSING;
    }
    else
    {
      character.set_trapped(1);
      scene.set_tile(pos.x, pos.y, TILE_CAGE);
    }
  }
  else if (tile_at_pos == TILE_KEY)
  {
    character.set_has_key(1);
    scene.set_tile(pos.x, pos.y, TILE_CORRIDOR);
    if (character.get_state() == STATE_FETCHING_KEY)
    {
      character.set_state(STATE_GOING_TO_CAGE);
    }
  }
  else if (tile_at_pos == TILE_CAGE)
  {
    if (character.get_has_key() && partner.is_trapped())
    {
      trigger_meetup_sequence(character, partner, scene, gameState);
      scene.set_tile(pos.x, pos.y, TILE_CORRIDOR);
    }
  }
}

void check_game_over_conditions(Character &p1, Character &p2, Scene &scene, int &gameState, int &moves_left)
{
  if (gameState == GAME_RUNNING)
  {
    int have_met = 0;
    Point p1_pos = p1.get_position();
    Point p2_pos = p2.get_position();
    bool p1_trapped = p1.is_trapped();
    bool p2_trapped = p2.is_trapped();

    if (p1_pos.x == p2_pos.x && p1_pos.y == p2_pos.y && !p1_trapped && !p2_trapped)
    {
      have_met = 1;
    }

    if (have_met)
    {
      trigger_meetup_sequence(p1, p2, scene, gameState);
      return;
    }
  }

  if (gameState == GAME_LOSING || gameState == GAME_DONE)
    return;

  if (p1.is_trapped() && p2.is_trapped())
  {
    gameState = GAME_LOSING;
  }
  else if ((p1.is_trapped() && p1.get_has_key()) || (p2.is_trapped() && p2.get_has_key()))
  {
    gameState = GAME_LOSING;
  }
  else if (moves_left <= 0)
  {
    gameState = GAME_LOSING;
  }

  if (gameState == GAME_WINNING)
  {
    Point ladder_pos = scene.get_ladder_position();
    if (p1.get_position().x == ladder_pos.x && p1.get_position().y == ladder_pos.y && p2.get_position().x == ladder_pos.x && p2.get_position().y == ladder_pos.y)
    {
      gameState = GAME_DONE;
    }
  }
}

void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, int &gameState)
{
  gameState = GAME_WINNING;

  if (p1.is_trapped())
    p1.set_trapped(0);
  if (p2.is_trapped())
    p2.set_trapped(0);

  scene.remove_obstacles(p1.get_position(), p2.get_position());

  p1.set_state(STATE_GOING_TO_LADDER);
  p2.set_state(STATE_GOING_TO_LADDER);
}