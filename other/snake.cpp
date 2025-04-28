#include <cursesw.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fmt/core.h>

#define MAXRAND 20

#define DELAY 100'000 // 0.1 seconds to microseconds

using fmt::format;
using std::vector, std::find, std::string;

struct Point
{
  int x, y;
  bool operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }
};

void place_food(Point &food, const vector<Point> &snake)
{
  while (true)
  {
    food.x = rand() % MAXRAND;
    food.y = rand() % MAXRAND;
    if (find(snake.begin(), snake.end(), food) == snake.end())
      break;
  }
}

void print_message_relative_to_center(Point dimensions, string msg, int rows_below_center = 0)
{
  mvprintw(dimensions.y / 2 + rows_below_center, (dimensions.y - msg.length()) / 2, "%s", msg.c_str());
}

int main()
{
  srand(time(NULL));

  WINDOW *win = initscr();
  keypad(win, true);
  nodelay(win, true);
  curs_set(0);

  Point dimensions;
  getmaxyx(win, dimensions.y, dimensions.x);

  vector<Point> snake = {{MAXRAND / 2, MAXRAND / 2}};

  Point food;
  Point dir = {1, 0};
  place_food(food, snake);

  int score = 0;
  bool game_over = false;

  while (!game_over)
  {
    int pressed = wgetch(win);

    if (pressed == KEY_LEFT && dir.x != 1)
    {
      dir = {-1, 0};
    }
    else if (pressed == KEY_RIGHT && dir.x != -1)
    {
      dir = {1, 0};
    }
    else if (pressed == KEY_UP && dir.y != 1)
    {
      dir = {0, -1};
    }
    else if (pressed == KEY_DOWN && dir.y != -1)
    {
      dir = {0, 1};
    }
    else if (pressed == 'q' || pressed == 'Q')
    {
      break;
    }

    Point new_head = {snake.front().x + dir.x, snake.front().y + dir.y};

    if (new_head.x < 0 || new_head.x >= MAXRAND ||
        new_head.y < 0 || new_head.y >= MAXRAND)
    {
      game_over = true;
      break;
    }

    if (find(snake.begin(), snake.end(), new_head) != snake.end())
    {
      game_over = true;
      break;
    }

    snake.insert(snake.begin(), new_head);

    if (new_head == food)
    {
      score++;
      place_food(food, snake);
    }
    else
    {
      snake.pop_back();
    }

    erase();

    for (int i = 0; i <= MAXRAND; ++i)
    {
      mvaddch(0, i, '#');
      mvaddch(MAXRAND, i, '#');
      mvaddch(i, 0, '#');
      mvaddch(i, MAXRAND, '#');
    }

    for (size_t i = 0; i < snake.size(); ++i)
    {
      mvaddch(snake[i].y + 1, snake[i].x + 1, i == 0 ? 'O' : '*');
    }

    mvaddch(food.y + 1, food.x + 1, '&');

    mvprintw(MAXRAND + 2, 0, "Score: %d", score);

    refresh();

    usleep(DELAY);
  }

  erase();

  print_message_relative_to_center(dimensions, "GAME OVER!");
  print_message_relative_to_center(dimensions, format("Final Score: {}", score), 1);
  print_message_relative_to_center(dimensions, "Press any key to exit...", 3);
  nodelay(win, false);
  wgetch(win);

  endwin();
  return 0;
}