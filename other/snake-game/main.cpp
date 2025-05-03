#include <curses.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <unordered_map>

#define DELAY 100'000 // 0.1 seconds to microseconds
#define HIGH_SCORE_FILE "highscore.bin"

using std::vector, std::find, std::string, std::fstream, std::ios, std::unordered_map, std::to_string;

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

enum class GameAction
{
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  QUIT,
  RESTART,
  NONE // No action / unrecognized key
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

void initialize_key_bindings(unordered_map<int, GameAction> &key_bindings)
{
  // Arrow Keys
  key_bindings[KEY_UP] = GameAction::MOVE_UP;
  key_bindings[KEY_DOWN] = GameAction::MOVE_DOWN;
  key_bindings[KEY_LEFT] = GameAction::MOVE_LEFT;
  key_bindings[KEY_RIGHT] = GameAction::MOVE_RIGHT;

  // WASD (lowercase and uppercase)
  key_bindings['w'] = GameAction::MOVE_UP;
  key_bindings['W'] = GameAction::MOVE_UP;
  key_bindings['s'] = GameAction::MOVE_DOWN;
  key_bindings['S'] = GameAction::MOVE_DOWN;
  key_bindings['a'] = GameAction::MOVE_LEFT;
  key_bindings['A'] = GameAction::MOVE_LEFT;
  key_bindings['d'] = GameAction::MOVE_RIGHT;
  key_bindings['D'] = GameAction::MOVE_RIGHT;

  // HJKL (lowercase and uppercase)
  key_bindings['k'] = GameAction::MOVE_UP;
  key_bindings['K'] = GameAction::MOVE_UP;
  key_bindings['j'] = GameAction::MOVE_DOWN;
  key_bindings['J'] = GameAction::MOVE_DOWN;
  key_bindings['h'] = GameAction::MOVE_LEFT;
  key_bindings['H'] = GameAction::MOVE_LEFT;
  key_bindings['l'] = GameAction::MOVE_RIGHT;
  key_bindings['L'] = GameAction::MOVE_RIGHT;

  // Q for quit
  key_bindings['q'] = GameAction::QUIT;
  key_bindings['Q'] = GameAction::QUIT;

  // R for quit
  key_bindings['r'] = GameAction::RESTART;
  key_bindings['R'] = GameAction::RESTART;
}

GameAction get_action(unordered_map<int, GameAction> key_bindings, int key)
{
  unordered_map<int, GameAction>::iterator it = key_bindings.find(key);
  if (it != key_bindings.end())
  {
    return it->second;
  }
  else
  {
    return GameAction::NONE;
  }
}

void print_message_relative_to_center(Point dimensions, string msg, int rows_below_center = 0)
{
  int start_col = (dimensions.x - msg.length()) / 2;
  if (start_col < 0)
    start_col = 0;
  mvprintw(dimensions.y / 2 + rows_below_center, start_col, "%s", msg.c_str());
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  unordered_map<int, GameAction> key_bindings;
  initialize_key_bindings(key_bindings);

  // Open file only for reading initially
  int highscore = 0;
  fstream read_file(HIGH_SCORE_FILE, ios::in | ios::binary);
  if (read_file.is_open())
  {
    read_file.read(reinterpret_cast<char *>(&highscore), sizeof(highscore));
    if (read_file.gcount() != sizeof(highscore))
    {
      // Handle error: file might be corrupted or incomplete
      highscore = 0;
    }
    read_file.close();
  }

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);
  leaveok(stdscr, true);   // Don't update cursor position
  scrollok(stdscr, false); // Disable scrolling

  Point dimensions;
  getmaxyx(stdscr, dimensions.y, dimensions.x);

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

  Food food;
  Point dir = {1, 0};
  place_food(food, snake, PLAY_SIZE);

  int score = 0;
  bool game_over = false;

  while (!game_over)
  {
    GameAction action = get_action(key_bindings, getch());

    if (action == GameAction::MOVE_LEFT && dir.x != 1)
    {
      dir = {-1, 0};
    }
    else if (action == GameAction::MOVE_RIGHT && dir.x != -1)
    {
      dir = {1, 0};
    }
    else if (action == GameAction::MOVE_UP && dir.y != 1)
    {
      dir = {0, -1};
    }
    else if (action == GameAction::MOVE_DOWN && dir.y != -1)
    {
      dir = {0, 1};
    }

    Point new_head = {snake.front().x + dir.x, snake.front().y + dir.y};

    if (new_head.x < 1 || new_head.x >= PLAY_SIZE - 1 ||
        new_head.y < 1 || new_head.y >= PLAY_SIZE - 1)
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

    if (new_head == food.position)
    {
      switch (food.type)
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
      place_food(food, snake, PLAY_SIZE);
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

    attron(COLOR_PAIR(food.type));
    mvaddch(food.position.y + 1, food.position.x + 1, '&');
    attroff(COLOR_PAIR(food.type));

    mvprintw(PLAY_SIZE + 2, 0, "Score: %d", score);

    refresh();

    usleep(DELAY);
  }

  erase();

  if (score > highscore)
  {
    highscore = score;
    // Open file for writing only when needed
    fstream write_file(HIGH_SCORE_FILE, ios::out | ios::binary);
    if (write_file.is_open())
    {
      write_file.write(reinterpret_cast<const char *>(&highscore), sizeof(highscore));
      write_file.close();
    }
  }

  print_message_relative_to_center(dimensions, "GAME OVER!");
  print_message_relative_to_center(dimensions, "Final Score: " + to_string(score), 1);
  print_message_relative_to_center(dimensions, "High Score: " + to_string(score), 2);
  print_message_relative_to_center(dimensions, "Press \"r\" to restart or \"q\" to exit...", 3);

  nodelay(stdscr, false);
  while (true)
  {
    GameAction action = get_action(key_bindings, getch());
    if (action == GameAction::QUIT)
    {
      break;
    }
    else if (action == GameAction::RESTART)
    {
      endwin();
      return main(argc, argv);
    }
  }

  endwin();
  return 0;
}