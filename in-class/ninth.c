#include <stdio.h>
#include <stdlib.h>

int main() {
  char c;
  printf("Give character (until .): ");
  do {
    c = getchar();
    if (c => '1' && c <= '9')
  } while (c != '.');
  return 0;
}
