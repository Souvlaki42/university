#ifndef STACK_H
#define STACK_H

typedef struct {
  int *start;
  int size;
  int cap;
} Stack;

void stack_init(Stack *stack, int cap);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);

typedef struct node {
  int value;
  struct node *next;
} Node;

void dstack_init(Node **stack);
void dstack_push(Node **stack, int value);
int dstack_pop(Node **stack);

#endif