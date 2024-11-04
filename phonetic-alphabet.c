#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  char ch;

  printf("Enter a string of characters (. to end): ");
  do
  {
    ch = getchar();

    if (ch == 'A' || ch == 'a')
      printf("Alfa");
    else if (ch == 'B' || ch == 'b')
      printf("Bravo");
    else if (ch == 'C' || ch == 'c')
      printf("Charlie");
    else if (ch == 'D' || ch == 'd')
      printf("Delta");
    else if (ch == 'E' || ch == 'e')
      printf("Echo");
    else if (ch == 'F' || ch == 'f')
      printf("Foxtrot");
    else if (ch == 'G' || ch == 'g')
      printf("Golf");
    else if (ch == 'H' || ch == 'h')
      printf("Hotel");
    else if (ch == 'I' || ch == 'i')
      printf("India");
    else if (ch == 'J' || ch == 'j')
      printf("Juliett");
    else if (ch == 'K' || ch == 'k')
      printf("Kilo");
    else if (ch == 'L' || ch == 'l')
      printf("Lima");
    else if (ch == 'M' || ch == 'm')
      printf("Mike");
    else if (ch == 'N' || ch == 'n')
      printf("November");
    else if (ch == 'O' || ch == 'o')
      printf("Oscar");
    else if (ch == 'P' || ch == 'p')
      printf("Papa");
    else if (ch == 'Q' || ch == 'q')
      printf("Quebec");
    else if (ch == 'R' || ch == 'r')
      printf("Romeo");
    else if (ch == 'S' || ch == 's')
      printf("Sierra");
    else if (ch == 'T' || ch == 't')
      printf("Tango");
    else if (ch == 'U' || ch == 'u')
      printf("Uniform");
    else if (ch == 'V' || ch == 'v')
      printf("Victor");
    else if (ch == 'W' || ch == 'w')
      printf("Whiskey");
    else if (ch == 'X' || ch == 'x')
      printf("X-Ray");
    else if (ch == 'Y' || ch == 'y')
      printf("Yankee");
    else if (ch == 'Z' || ch == 'z')
      printf("Zulu");
    else if (ch >= '0' && ch <= '9')
      for (int i = 0; i < ch - '0'; i++)
        printf("*");
    else
      printf("%c", ch);
  } while (ch != '.');

  return 0;
}