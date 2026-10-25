#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  fclose(fp);
  return 0;
}
