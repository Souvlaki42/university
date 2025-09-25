#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "scene.h"
#include "character.h"
#include "utils.h"

using std::cerr, std::exception, std::string, std::vector;

void process_character_move(Character &character, Character &partner, Scene &scene, GameState &gameState);
void check_game_over_conditions(Character &p1, Character &p2, Scene &scene, GameState &gameState, int &moves_left);
void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, GameState &gameState);

//! Οδηγίες: https://docs.google.com/document/d/12qdicYiuhyEsiSzJqg7Vp2uN0f_mEO32C6b3-flJtj0/edit?tab=t.0
int main(int argc, char *argv[])
{
  srandom(time(NULL));

  if (argc < 2)
  {
    cerr << "Σφάλμα: Δεν δόθηκε αρχείο χάρτη.\n";
    return 1;
  }

  try
  {
    Scene scene = Scene(string(argv[1]));
    Character grigorakis = Character(scene, 'G', false);
    Character asimenia = Character(scene, 'S', false);

    scene.place_characters(grigorakis, asimenia);

    GameState gameState = GameState::RUNNING;
    int moves_left = MAX_MOVES;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    timeout(0);
    curs_set(0);
    leaveok(stdscr, true);
    scrollok(stdscr, false);

    scene.render();
    grigorakis.render();
    asimenia.render();
    refresh();

    usleep(FRAME_DELAY_MS);

    while (gameState != GameState::DONE)
    {
      if (getch() == 'q')
      {
        break;
      }

      if (gameState == GameState::RUNNING || gameState == GameState::WINNING)
      {
        grigorakis.update(asimenia);
        process_character_move(grigorakis, asimenia, scene, gameState);

        if (gameState == GameState::RUNNING || gameState == GameState::WINNING)
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

      if (gameState == GameState::LOSING || (gameState == GameState::DONE && moves_left >= 0))
      {
        timeout(-1);
        getch();
        break;
      }

      usleep(FRAME_DELAY_MS);
    }

    endwin();
  }
  catch (const exception &e)
  {
    endwin();
    cerr << "Ένα ανεπανόρθωτο σφάλμα προέκυψε: " << e.what() << "\n";
    return 1;
  }

  return 0;
}

void process_character_move(Character &character, Character &partner, Scene &scene, GameState &gameState)
{
  if (gameState == GameState::LOSING || gameState == GameState::DONE)
    return;

  Point pos = character.get_position();
  Tile tile_at_pos = scene.get_tile(pos.x, pos.y);

  if (tile_at_pos == Tile::TRAP)
  {
    if (character.get_has_key())
    {
      gameState = GameState::LOSING;
    }
    else
    {
      character.set_trapped(true);
      scene.set_tile(pos.x, pos.y, Tile::CAGE);
    }
  }
  else if (tile_at_pos == Tile::KEY)
  {
    character.set_has_key(true);
    scene.set_tile(pos.x, pos.y, Tile::CORRIDOR);
    if (character.get_state() == CharacterState::FETCHING_KEY)
    {
      character.set_state(CharacterState::GOING_TO_CAGE);
    }
  }
  else if (tile_at_pos == Tile::CAGE)
  {
    if (character.get_has_key() && partner.is_trapped())
    {
      trigger_meetup_sequence(character, partner, scene, gameState);
      scene.set_tile(pos.x, pos.y, Tile::CORRIDOR);
    }
  }
}

void check_game_over_conditions(Character &p1, Character &p2, Scene &scene, GameState &gameState, int &moves_left)
{
  if (gameState == GameState::RUNNING)
  {
    bool have_met = false;
    Point p1_pos = p1.get_position();
    Point p2_pos = p2.get_position();
    bool p1_trapped = p1.is_trapped();
    bool p2_trapped = p2.is_trapped();

    if (p1_pos == p2_pos && !p1_trapped && !p2_trapped)
    {
      have_met = true;
    }

    if (!have_met)
    {
      vector<Point> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};
      for (const Point &dir : directions)
      {
        if (p1_pos.x + dir.x == p2_pos.x && p1_pos.y + dir.y == p2_pos.y && !p1_trapped && !p2_trapped)
        {
          have_met = true;
          break;
        }
      }
    }

    if (have_met)
    {
      trigger_meetup_sequence(p1, p2, scene, gameState);
      return;
    }
  }

  if (gameState == GameState::LOSING || gameState == GameState::DONE)
    return;

  if (p1.is_trapped() && p2.is_trapped())
  {
    gameState = GameState::LOSING;
  }
  else if ((p1.is_trapped() && p1.get_has_key()) || (p2.is_trapped() && p2.get_has_key()))
  {
    gameState = GameState::LOSING;
  }
  else if (moves_left <= 0)
  {
    gameState = GameState::LOSING;
  }

  if (gameState == GameState::WINNING)
  {
    Point ladder_pos = scene.get_ladder_position();
    if (p1.get_position() == ladder_pos && p2.get_position() == ladder_pos)
    {
      gameState = GameState::DONE;
    }
  }
}

void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, GameState &gameState)
{
  gameState = GameState::WINNING;

  if (p1.is_trapped())
    p1.set_trapped(false);
  if (p2.is_trapped())
    p2.set_trapped(false);

  scene.remove_obstacles(p1.get_position(), p2.get_position());

  p1.set_state(CharacterState::GOING_TO_LADDER);
  p2.set_state(CharacterState::GOING_TO_LADDER);
}