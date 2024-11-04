#include <stdio.h>

void printBinary(char num)
{
  for (int i = 7; i >= 0; i--)
  {
    printf("%d", (num >> i) & 1);
  }
}

void printChar(char num)
{
  printf("%c    | %d  | ", num, num);
  printBinary(num);
  printf(" | %o   | %x       \n", num, num);
}

int main(void)
{
  printf("Char | Dec |   Bin    | Octal | Hex \n");

  for (char i = 65; i < 75; i++)
  {
    printChar(i);
  }

  return 0;
}
