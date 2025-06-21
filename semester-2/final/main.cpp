#include <cursesw.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <locale.h>
#include "scene.h"
#include "character.h"
#include "utils.h"

void process_character_move(Character &character, Character &partner, Scene &scene, GameState &gameState);
void check_game_over_conditions(Character &p1, Character &p2, Scene &scene, GameState &gameState, int &moves_left);
void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, GameState &gameState);

//! Οδηγίες: https://docs.google.com/document/d/12qdicYiuhyEsiSzJqg7Vp2uN0f_mEO32C6b3-flJtj0/edit?tab=t.0
int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  srandom(time(NULL));

  if (argc < 2)
  {
    std::cerr << "Σφάλμα: Δεν δόθηκε αρχείο χάρτη.\n";
    return 1;
  }

  try
  {
    Scene scene = Scene(std::string(argv[1]));
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

    scene.log_event(L"Πάτα 'q' για να τερματήσεις την προσομοίωση.");

    scene.log(L"Τέρμινα", moves_left);
    scene.log(L"Κατάσταση", gameState);

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
        scene.log(L"Τέρμινα", moves_left);
        scene.log(L"Κατάσταση", gameState);

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
  catch (const std::exception &e)
  {
    endwin();
    std::cerr << "Ένα ανεπανόρθωτο σφάλμα προέκυψε: " << e.what() << "\n";
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
      scene.log_event(L"ΑΠΟΤΥΧΙΑ: Ο χαρακτήρας έπεσε σε παγίδα ενώ είχε το κλειδί!");
      gameState = GameState::LOSING;
    }
    else
    {
      character.set_trapped(true);
      scene.set_tile(pos.x, pos.y, Tile::CAGE);
      scene.log_event(L"Ένας χαρακτήρας παγιδεύτηκε!");
    }
  }
  else if (tile_at_pos == Tile::KEY)
  {
    character.set_has_key(true);
    scene.set_tile(pos.x, pos.y, Tile::CORRIDOR);
    scene.log_event(L"Το κλειδί βρέθηκε!");
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

    if (p1_pos == p2_pos)
    {
      have_met = true;
    }

    if (!have_met)
    {
      std::vector<Point> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1}};
      for (const Point &dir : directions)
      {
        if (p1_pos.x + dir.x == p2_pos.x && p1_pos.y + dir.y == p2_pos.y)
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
    scene.log_event(L"ΑΠΟΤΥΧΙΑ: Και οι δύο χαρακτήρες παγιδεύτηκαν!");
  }
  else if ((p1.is_trapped() && p1.get_has_key()) || (p2.is_trapped() && p2.get_has_key()))
  {
    gameState = GameState::LOSING;
    scene.log_event(L"ΑΠΟΤΥΧΙΑ: Ο χαρακτήρας με το κλειδί παγιδεύτηκε!");
  }
  else if (moves_left <= 0)
  {
    gameState = GameState::LOSING;
    scene.log_event(L"ΑΠΟΤΥΧΙΑ: Ο χρόνος τελείωσε!");
  }

  if (gameState == GameState::WINNING)
  {
    Point ladder_pos = scene.get_ladder_position();
    if (p1.get_position() == ladder_pos && p2.get_position() == ladder_pos)
    {
      gameState = GameState::DONE;
      scene.log_event(L"ΝΙΚΗ: Το βασίλειο σώθηκε!");
    }
  }
}

void trigger_meetup_sequence(Character &p1, Character &p2, Scene &scene, GameState &gameState)
{
  scene.log_event(L"ΝΙΚΗ: Οι χαρακτήρες συναντήθηκαν! Τώρα προς τη σκάλα!");
  gameState = GameState::WINNING;

  if (p1.is_trapped())
    p1.set_trapped(false);
  if (p2.is_trapped())
    p2.set_trapped(false);

  scene.remove_obstacles(p1.get_position(), p2.get_position());

  p1.set_state(CharacterState::GOING_TO_LADDER);
  p2.set_state(CharacterState::GOING_TO_LADDER);
}