#include "libStack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_init(Stack *stack, int cap) {
  stack->cap = cap;
  stack->start = malloc(stack->cap * sizeof(int));
  stack->size = -1;
}

void stack_push(Stack *stack, int value) {
  if (stack->size >= stack->cap - 1) {
    fprintf(stderr, "Η στοίβα ξεχίλησε\n");
    return;
  }

  stack->size++;
  *(stack->start + stack->size) = value;
}

int stack_pop(Stack *stack) {
  if (stack->size == -1) {
    fprintf(stderr, "Η στοίβα υποχείλησε\n");
    return -1;
  }

  int value = *(stack->start + stack->size);
  stack->size--;

  if (stack->size < 0) {
    free(stack->start);
    stack->start = NULL;
    stack->size = -1;
    stack->cap = 0;
    printf("Η στοίβα δεν χρείαζεται πλέον, η μνήμη αποδεσμεύτηκε\n");
  }

  return value;
}