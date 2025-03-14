#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
  char difficulty[10];
  do
  {
    printf("Enter the difficulty level (easy, medium, hard): ");
    scanf("%s", difficulty);
  } while (strcmp(difficulty, "easy") && strcmp(difficulty, "medium") && strcmp(difficulty, "hard"));

  printf("You chose %s difficulty.\n", difficulty);

  /*
  a. difficulty != "easy" and difficulty != "medium" and difficulty != "hard"
  b. !strcmp(difficulty, "easy") || !strcmp(difficulty, "medium") || !strcmp(difficulty, "hard")
  c. strcmp(difficulty, "easy") || strcmp(difficulty, "medium") || strcmp(difficulty, "hard")
  d. strcmp(difficulty, "easy") && strcmp(difficulty, "medium") && strcmp(difficulty, "hard")
  */

  return 0;
}