#include "libStack.h"
#include <stdio.h>

int main(void) {
  printf("Στατική στοίβα:\n");

  Stack stack = {0};
  stack_init(&stack, 15);

  for (int i = 1; i <= 15; i++) {
    printf("%dο εισαγωγή στοίβας: %d\n", i, i);
    stack_push(&stack, i);
  }

  for (int i = 1; i <= 15; i++) {
    printf("%dο εξαγωγή στοίβας: %d\n", i, stack_pop(&stack));
  }

  printf("Δυναμική στοίβα:\n");

  Node *stack2 = {0};
  // dstack_init(stack2);

  for (int i = 1; i <= 15; i++) {
    printf("%dο εισαγωγή στοίβας: %d\n", i, i);
    dstack_push(&stack2, i);
  }

  for (int i = 1; i <= 15; i++) {
    printf("%dο εξαγωγή στοίβας: %d\n", i, dstack_pop(&stack2));
  }

  return 0;
}