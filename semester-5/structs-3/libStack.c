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
    fprintf(stderr, "Η στοίβα άδειασε\n");
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

void dstack_init(Node *stack) {
  Node *new_item = malloc(sizeof(Node));
  if (new_item == NULL) {
    fprintf(stderr, "Η στοίβα ξεχίλησε\n");
    return;
  }
  new_item->value = 0;
  new_item->next = NULL;
  stack = new_item;
}

void dstack_push(Node **stack, int value) {
  Node *new_item = malloc(sizeof(Node));
  if (new_item == NULL) {
    fprintf(stderr, "Η στοίβα ξεχίλησε\n");
    return;
  }

  new_item->value = value;
  new_item->next = *stack;
  *stack = new_item;
}

int dstack_pop(Node **stack) {
  if (*stack == NULL) {
    fprintf(stderr, "Η στοίβα άδειασε\n");
    return -1;
  }

  int value = (*stack)->value;
  Node *temp = *stack;
  *stack = (*stack)->next;
  free(temp);
  return value;
}