#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BASE_LETTER_SCORE 10
#define BASE_GUESS_BONUS 100
#define MAX_STRING_LENGTH 100

// NOTE: Make sure to free the memory allocated for the lines array
// NOTE: Make sure to close the file
// NOTE: Make sure to not free the line memory before the end of the main function

char *getRandomLineWithLength(FILE *file, int length)
{
  char **lines = NULL;
  int line_count = 0;

  int line_number = 1;
  while (1)
  {
    char *line = NULL;
    size_t line_length = 0;
    int c;

    while ((c = fgetc(file)) != '\n' && c != EOF)
    {
      line_length++;
      line = realloc(line, line_length * sizeof(char));
      if (line == NULL)
      {
        return NULL;
      }
      line[line_length - 1] = c;
    }

    // If we reached the end of the file, break out of the loop
    if (c == EOF)
    {
      break;
    }

    // Add a null terminator to the end of the line
    line = realloc(line, (line_length + 1) * sizeof(char));
    if (line == NULL)
    {
      return NULL;
    }
    line[line_length] = '\0';

    if (line_length == length)
    {
      lines = realloc(lines, (line_count + 1) * sizeof(char *));
      if (lines == NULL)
      {
        return NULL;
      }
      lines[line_count++] = line;
    }

    line_number++;
  }
  char *line = lines[rand() % line_count];
  free(lines);
  return line;
}

char *shuffleString(char *str)
{
  // Use Fisher-Yates shuffle to shuffle the string
  int length = strlen(str);
  for (int i = 0; i < length; i++)
  {
    int j = rand() % (length - i) + i;
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
  return str;
}

int calculateScore(int word_length, int guesses)
{
  int baseScore = word_length * BASE_LETTER_SCORE;
  int guessBonus = BASE_GUESS_BONUS - (guesses - 1) * (BASE_LETTER_SCORE) / 2;
  if (guessBonus < 0)
    guessBonus = 0;
  return baseScore + guessBonus;
}

char *getDateTime()
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  static char buffer[MAX_STRING_LENGTH];
  strftime(buffer, MAX_STRING_LENGTH, "%d/%m/%Y %H:%M", timeinfo);
  return buffer;
}

struct GameResult
{
  int score;
  int exit_code;
};

struct GameResult playGame(FILE *file, int length)
{
  int score = 0;
  char *input = malloc(length * sizeof(char));
  while (1)
  {
    int guesses = 0;
    char *line = getRandomLineWithLength(file, length);

    if (line == NULL)
    {
      printf("Error allocating memory\n");
      return (struct GameResult){0, EXIT_FAILURE};
    }

    printf("Line: %s\n", line);
    char *line_copy = strdup(line);
    line = shuffleString(line);
    printf("Shuffled line: %s\n", line);

    while (1)
    {
      guesses++;
      printf("Give your guess of the original word: ");
      scanf("%s", input);
      if (strcmp(input, line_copy) == 0)
      {
        score += calculateScore(length, guesses);
        printf("Correct!\n");
        printf("Do you want to play again? (y/n): ");
        char answer;
        scanf(" %c", &answer);
        free(line);
        free(line_copy);
        if (answer == 'y')
        {
          rewind(file); // rewind the file to the beginning
          length++;
          break; // break out of the inner loop
        }
        else
        {
          free(input);
          return (struct GameResult){score, EXIT_SUCCESS};
        }
      }
      else
      {
        printf("Incorrect!\n");
        continue;
      }
    }
  }
}

struct ScoreEntry
{
  char name[MAX_STRING_LENGTH];
  char *datetime;
  int score;
};

int saveScore(int score)
{
  printf("You scored %d\n", score);
  printf("The game has ended, do you want to save your score? (y/n): ");
  char answer;
  scanf(" %c", &answer);
  if (answer == 'y')
  {
    FILE *scoreFile = fopen("scores.bin", "ab");
    if (scoreFile == NULL)
    {
      printf("file can't be opened");
      return EXIT_FAILURE;
    }

    char name[MAX_STRING_LENGTH];
    printf("Give your name: ");
    scanf("%s", name);

    char *dateTime = getDateTime();

    struct ScoreEntry entry = {
        .score = score,
        .datetime = dateTime,
    };

    strncpy(entry.name, name, MAX_STRING_LENGTH);

    fwrite(&entry, sizeof(struct ScoreEntry), 1, scoreFile);

    fclose(scoreFile);
    free(dateTime);
  }

  return EXIT_SUCCESS;
}

int startGame()
{
  srand(time(NULL)); // Seed the random number generator

  FILE *wordsFile = fopen("american-english", "r");
  if (wordsFile == NULL)
  {
    printf("file can't be opened");
    return EXIT_FAILURE;
  }

  size_t length = 5;
  struct GameResult result = playGame(wordsFile, length);
  fclose(wordsFile);

  if (result.exit_code == EXIT_FAILURE)
    return EXIT_FAILURE;

  int exit_code = saveScore(result.score);

  if (exit_code == EXIT_FAILURE)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

int printTopScores()
{
  FILE *scoreFile = fopen("scores.bin", "rb");
  if (!scoreFile)
  {
    printf("Cannot open scores file\n");
    return EXIT_FAILURE;
  }

  struct ScoreEntry *entries = NULL;
  int numEntries = 0;

  while (1)
  {
    entries = realloc(entries, (numEntries + 1) * sizeof(struct ScoreEntry));
    if (!entries)
    {
      printf("Memory allocation failed\n");
      fclose(scoreFile);
      return EXIT_FAILURE;
    }

    if (fread(&entries[numEntries], sizeof(struct ScoreEntry), 1, scoreFile) != 1)
    {
      break;
    }
    numEntries++;
  }
  fclose(scoreFile);

  // Sort and print top 10 like before
  for (int i = 0; i < numEntries - 1; i++)
  {
    for (int j = 0; j < numEntries - i - 1; j++)
    {
      if (entries[j].score < entries[j + 1].score)
      {
        struct ScoreEntry temp = entries[j];
        entries[j] = entries[j + 1];
        entries[j + 1] = temp;
      }
    }
  }

  printf("Top 10 Scores:\n");
  int limit = numEntries < 10 ? numEntries : 10;
  for (int i = 0; i < limit; i++)
  {
    printf("%s %s %d\n",
           entries[i].name, entries[i].datetime, entries[i].score);
  }

  free(entries);

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
  int exit_code = EXIT_SUCCESS;
  if (argc == 2 && strcmp(argv[1], "--highscore") == 0)
  {
    exit_code = printTopScores();
  }
  else
  {
    exit_code = startGame();
  }

  return exit_code;
}