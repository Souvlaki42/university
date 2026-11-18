#include "libStack.h"
#include <stdio.h>

int main(void) {
  Stack stack = {0};
  stack_init(&stack, 15);

  for (int i = 1; i <= 15; i++) {
    printf("%dο εισαγωγή στοίβας: %d\n", i, i);
    stack_push(&stack, i);
  }

  for (int i = 1; i <= 15; i++) {
    printf("%dο εξαγωγή στοίβας: %d\n", i, stack_pop(&stack));
  }

  return 0;
}