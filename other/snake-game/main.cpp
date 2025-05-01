#include <cursesw.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <string>
#include <format>
#include <fstream>

#define DELAY 100'000 // 0.1 seconds to microseconds
#define HIGH_SCORE_FILE "highscore.txt"

using std::vector, std::find, std::string, std::format, std::fstream, std::ios;

struct Point
{
  int x, y;
  bool operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }
};

enum class FoodType
{
  Normal = 2,
  Poison = 3,
  MultiplePoints = 4,
  Shrink = 5,
};

struct Food
{
  Point position;
  FoodType type;
};

void place_food(Food &food, const vector<Point> &snake, const int PLAY_SIZE)
{
  while (true)
  {
    food.position.x = 1 + (random() % (PLAY_SIZE - 2));
    food.position.y = 1 + (random() % (PLAY_SIZE - 2));

    int chance = random() % 20;
    food.type = chance > 2 ? FoodType::Normal : chance > 1 ? FoodType::Poison
                                            : chance > 0   ? FoodType::MultiplePoints
                                                           : FoodType::Shrink;
    if (find(snake.begin(), snake.end(), food.position) == snake.end())
      break;
  }
}

void print_message_relative_to_center(Point dimensions, string msg, int rows_below_center = 0)
{
  int start_col = (dimensions.x - msg.length()) / 2;
  if (start_col < 0)
    start_col = 0;
  mvprintw(dimensions.y / 2 + rows_below_center, start_col, "%s", msg.c_str());
}

int main()
{

  srand(time(NULL));

  // Open file only for reading initially
  fstream read_file(HIGH_SCORE_FILE, ios::in);
  int highscore = 0;

  if (read_file.is_open())
  {
    read_file >> highscore;
    read_file.close();
  }

  WINDOW *win = initscr();
  cbreak();
  noecho();
  keypad(win, true);
  nodelay(win, true);
  curs_set(0);

  Point dimensions;
  getmaxyx(win, dimensions.y, dimensions.x);

  if (has_colors())
  {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
  }

  const int PLAY_SIZE = (dimensions.y / 10) * 10;

  vector<Point> snake = {{PLAY_SIZE / 2, PLAY_SIZE / 2}};

  Food apple;
  Point dir = {1, 0};
  place_food(apple, snake, PLAY_SIZE);

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

    Point new_head = {snake.front().x + dir.x, snake.front().y + dir.y};

    if (new_head.x < 0 || new_head.x >= PLAY_SIZE ||
        new_head.y < 0 || new_head.y >= PLAY_SIZE)
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

    if (new_head == apple.position)
    {
      switch (apple.type)
      {
      case FoodType::Normal:
        score++;
        break;
      case FoodType::Poison:
        score--;
        break;
      case FoodType::MultiplePoints:
        score += random() % 9 + 2;
        break;
      case FoodType::Shrink:
        int parts_to_remove = random() % (snake.size() - 1) + 1;
        for (int i = 0; i < parts_to_remove; i++)
        {
          snake.pop_back();
        }
        break;
      }
      place_food(apple, snake, PLAY_SIZE);
    }
    else
    {
      snake.pop_back();
    }

    erase();

    for (int i = 0; i <= PLAY_SIZE; ++i)
    {
      mvaddch(0, i, '#');
      mvaddch(PLAY_SIZE, i, '#');
      mvaddch(i, 0, '#');
      mvaddch(i, PLAY_SIZE, '#');
    }

    attron(COLOR_PAIR(3));
    for (size_t i = 0; i < snake.size(); ++i)
    {
      mvaddch(snake[i].y + 1, snake[i].x + 1, i == 0 ? 'O' : '*');
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(apple.type));
    mvaddch(apple.position.y + 1, apple.position.x + 1, '&');
    attroff(COLOR_PAIR(apple.type));

    mvprintw(PLAY_SIZE + 2, 0, "Score: %d", score);

    refresh();

    usleep(DELAY);
  }

  erase();

  if (score > highscore)
  {
    highscore = score;
    // Open file for writing only when needed
    fstream write_file(HIGH_SCORE_FILE, ios::out);
    if (write_file.is_open())
    {
      write_file << highscore;
      write_file.close();
    }
  }

  print_message_relative_to_center(dimensions, "GAME OVER!");
  print_message_relative_to_center(dimensions, format("Final Score: {}", score), 1);
  print_message_relative_to_center(dimensions, format("High Score: {}", highscore), 2);
  print_message_relative_to_center(dimensions, "Press \"q\" to exit...", 3);

  nodelay(win, false);
  while (true)
  {
    int ch = wgetch(win);
    if (ch == 'q' || ch == 'Q')
    {
      break;
    }
  }

  endwin();

  return 0;
}