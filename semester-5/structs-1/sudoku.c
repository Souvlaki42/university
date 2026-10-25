#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** create_board(int, int);
int read_puzzle(FILE *, char **);
int check_line(char *, int);
int check_duplicates(char *);
void print_board(char **);
int check_board(char **);

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
  
  status = read_puzzle(fp, board);
  
  if (status == -2) {
    fprintf(stderr, "Αδυναμία δέσμέυσης μνήμης\n");
  }

  if (status == -1) {
    fprintf(stderr, "Πρόβλημα με το περιεχόμενο του αρχείου %s\n", argv[1]);
    return 1;
  }

  printf("Το sudoku στην αρχή:\n");
  print_board(board);

  check_board(board);

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

int read_puzzle(FILE *fp, char **board) {
  char* buf = malloc(11);
  if (buf == NULL) {
    free(buf);
    return -2;
  }

  for (int row = 0; row < 9; row++) {
    fgets(buf, 11, fp);
    if (check_line(buf, row) == -1) {
      free(buf);
      return -1;
    }
    for (int col = 0; col < 9; col++) {
      board[row][col] = buf[col];
    }
  }
  free(buf);
  return 0;
}

int check_line(char *line, int row) {
  for (int col = 0; col < 9; col++)
    if (line[col] < '0' || line[col] > '9') {
      fprintf(stderr, "Γραμμή %d: Ο χαρακτήρας %c δεν είναι αριθμος\n", row + 1, line[col]);
      return -1;
    }
  if (line[9] != '\n') {
    fprintf(stderr, "Γραμμή %d: Λείπει ο χαρακτήρας αλλαγής γραμμής\n", row + 1);
    return -1;
  }
  return 0;
}

void print_board(char **board) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      putchar(board[row][col]);
      if (col % 3 == 2) putchar(' ');
    }
    putchar('\n');
    if (row % 3 == 2) putchar('\n');
  }
}

int check_duplicates(char *nines) {
  int* check = calloc(9, sizeof(int));

  for (int pos = 0; pos < 9; pos++) {
    int num = nines[pos] - '0';
    if (num == 0) continue;
    check[num - 1] += 1;
    if (check[num - 1] > 1) {
      free(check);
      return pos;
    } 
  }

  free(check);
  return 0;
}

int check_board(char **board) {
  char* nines = malloc(9);

  // Ελέγχω γραμμές
  for (int row = 0; row < 9; row++) {
    memcpy(nines, board[row], 9);
    int dups = check_duplicates(nines);
    if (dups > 0) {
      printf("Σειρά %d: Ο αριθμός %c επαναλαμβάνεται\n", dups + 1, nines[dups]);
      free(nines);
      return -1;
    }
  }

  // Ελέγχω στήλες
  for (int col = 0; col < 9; col++) {
    for (int row = 0; row < 9; row++) {
      nines[row] = board[row][col];
    }
    int dups = check_duplicates(nines);
    if (dups > 0) {
      printf("Στήλη %d: Ο αριθμός %c επαναλαμβάνεται\n", dups + 1, nines[dups]);
      free(nines);
      return -1;
    }
  }

  // Ελέγχω τετράγωνα
  for (int i = 0; i < 9; i++) {
    int p = 0;
    int y = i / 3 * 3;
    int x = i % 3 * 3;
    for (int row = y; row <= y + 2; row++) {
      for (int col = x; col <= x + 2; col++) {
        nines[p++] = board[row][col]; 
      }
    }
    int dups = check_duplicates(nines);
    if (dups > 0) {
      printf("Τετράγωνο %d: Ο αριθμός %c επαναλαμβάνεται\n", i, nines[dups]);
      free(nines);
      return -1;
    }
  }

  free(nines);
  return 0;
}