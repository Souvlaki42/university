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

  while (abs(asimenia.get_position().x - grigorakis.get_position().x) < 7 &&
         abs(asimenia.get_position().y - grigorakis.get_position().y) < 7)
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

  bool is_game_over = false;

  while (!is_game_over)
  {
    erase();

    scene.render();
    grigorakis.render();
    asimenia.render();

    grigorakis.move_generic();
    asimenia.move_generic();

    refresh();
    usleep(DELAY);

    if (getch() == 'q')
    {
      is_game_over = true;
    }
  }

  endwin();
  return 0;
}
