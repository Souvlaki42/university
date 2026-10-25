#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** create_board(int, int);
int main(int argc, char **argv) {
  int status = 0;

  if (argc != 2) {
    fprintf(stderr, "Λάθος παράμετροι. Χρήση: %s <όνομα αρχείου>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Αδυναμία ανοίγματος αρχείου %s\n", argv[1]);
    return 1;
  }

  char **board = create_board(9, 9);
  
  if (board == NULL) {
    fprintf(stderr, "Αδυναμία δέσμέυσης μνήμης\n");
  }
  fclose(fp);
  for (int i = 0; i < 9; i++) {
    free(board[i]);
  }
  free(board);
  return 0;
}

char **create_board(int width, int height) {
  char **board = calloc(height, sizeof(char *));
  if (board == NULL) return NULL;

  for (int row = 0; row < height; row++) {
    board[row] = malloc(width);
    if (board[row] == NULL) {
      for (int i = 0; i < row; i++) free(board[i]);
      free(board);
      return NULL;
    }
  }

  return board;
}
