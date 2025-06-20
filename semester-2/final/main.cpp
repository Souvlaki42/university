#include <cursesw.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <locale.h>
#include "scene.h"
#include "character.h"

using std::cerr, std::string;

//! Οδηγίες: https://docs.google.com/document/d/12qdicYiuhyEsiSzJqg7Vp2uN0f_mEO32C6b3-flJtj0/edit?tab=t.0
int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  srandom(time(NULL));

  if (argc < 2)
  {
    cerr << "Σφάλμα: Δεν δόθηκε αρχείο χάρτη.\n";
    return 1;
  }

  try
  {
    Scene scene = Scene(string(argv[1]));
    Character grigorakis = Character(scene, 'G');
    Character asimenia = Character(scene, 'S');

    scene.place_characters(grigorakis, asimenia);

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

    while (scene.is_running())
    {
      grigorakis.update(asimenia);
      asimenia.update(grigorakis);
      scene.update();

      erase();
      scene.render();
      grigorakis.render();
      asimenia.render();
      refresh();

      usleep(FRAME_DELAY_MS);
    }

    endwin();
  }
  catch (const std::exception &e)
  {
    endwin();
    cerr << "Ένα ανεπανόρθωτο σφάλμα προέκυψε: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
