#include <curses.h>
#include <stdlib.h>
#include <string.h>

#define DELAY 1000

// minimal ncurses starter template
int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);
  leaveok(stdscr, true);
  scrollok(stdscr, false);

  int width, height = 0;
  getmaxyx(stdscr, height, width);

  bool finished = false;

  while (!finished) {
    refresh();

    usleep(DELAY);
  }

  erase();
  endwin();

  return 0;
}