#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 20
#define COLS 100

int main(void) {
  srand(time(NULL));
  int nums[ROWS][COLS], num;
  int res[ROWS] = {0};
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      nums[i][j] = rand() % 5 + 5;
    }
  }
  printf("Give a number: ");
  scanf("%d", &num);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (nums[i][j] == num)
        res[i]++;
      printf("%2d ", nums[i][j]);
    printf("\t%d\n", res[i]);
    }
  }
}
