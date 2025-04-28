#include <cursesw.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXRAND 20

int main()
{
  srand(time(NULL));

  WINDOW *win = initscr();
  keypad(win, true);
  nodelay(win, true);

  int posX = 0;
  int posY = 0;

  int foodX = rand() % MAXRAND;
  int foodY = rand() % MAXRAND;

  int dirX = 1;
  int dirY = 0;

  int score = 0;

  while (true)
  {
    int pressed = wgetch(win);

    if (pressed == KEY_LEFT)
    {
      dirX = -1;
      dirY = 0;
    }

    if (pressed == KEY_RIGHT)
    {
      dirX = 1;
      dirY = 0;
    }

    if (pressed == KEY_UP)
    {
      dirX = 0;
      dirY = -1;
    }

    if (pressed == KEY_DOWN)
    {
      dirX = 0;
      dirY = 1;
    }

    posX += dirX;
    posY += dirY;

    erase();
    mvaddstr(posY, posX, "*");
    mvaddstr(foodY, foodX, "&");

    if (posX == foodX && posY == foodY)
    {
      score++;
      foodX = rand() % MAXRAND;
      foodY = rand() % MAXRAND;
    }

    usleep(100000);
  }

  endwin();

  return 0;
}