#include <curses.h>
#include <unistd.h>
#include "scene.h"
#include "character.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

using std::cout, std::cerr, std::string, std::ifstream;

#define DELAY 1'000'000 // 1 second to microseconds

//! Instructions: https://docs.google.com/document/d/12qdicYiuhyEsiSzJqg7Vp2uN0f_mEO32C6b3-flJtj0/edit?tab=t.0
int main(int argc, char *argv[])
{
  srand(time(NULL));

  if (argc < 2)
  {
    cerr << "Σφάλμα: Δεν δόθηκε αρχείο χάρτη.\n";
    return 1;
  }

  Scene scene = Scene(argv[1]);

  if (!scene.is_open())
  {
    cerr << "Σφάλμα: Το αρχείο χάρτη δεν μπόρεσε να ανοιχθεί.\n";
    return 1;
  }

  Character grigorakis = Character(scene, 'G');
  Character asimenia = Character(scene, 'S');

  while ((scene.get_tile(grigorakis.get_position().x, grigorakis.get_position().y) != Tile::CORRIDOR) ||
         (scene.get_tile(asimenia.get_position().x, asimenia.get_position().y) != Tile::CORRIDOR) ||
         (abs(asimenia.get_position().x - grigorakis.get_position().x) < 7 && abs(asimenia.get_position().y - grigorakis.get_position().y) < 7))
  {
    asimenia.set_random_position();
    grigorakis.set_random_position();
  }

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);
  leaveok(stdscr, true);   // Don't update cursor position
  scrollok(stdscr, false); // Disable scrolling

  while (scene.get_state() != GameState::DONE)
  {
    erase();

    scene.render();
    grigorakis.render();
    asimenia.render();

    grigorakis.move();
    asimenia.move();

    if (grigorakis.get_position() == asimenia.get_position())
    {
      scene.set_state(GameState::WINNING);
    }

    wnoutrefresh(stdscr);
    doupdate();

    usleep(DELAY);

    scene.update();
  }

  endwin();
  return 0;
}
