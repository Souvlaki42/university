#include <stdio.h>

int main(void) {
  int input;
  printf("Give a value in celcius: ");
  scanf("%d", &input);
  printf("Your input in celcius is %d is %.2f in farenheit\n", input, (9.0/5) * input + 32);
  for (int i = 0; i <= 100; i+=5)
   printf("Celcius: %d Farenheit: %.2f\n", i, (9.0/5)*i+32);
  return 0;
}
