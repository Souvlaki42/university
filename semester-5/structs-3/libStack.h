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

typedef struct {
  int *start;
  int size;
  int cap;
} DynamicStack;

void dstack_init(DynamicStack *stack);
void dstack_push(DynamicStack *stack, int value);
int dstack_pop(DynamicStack *stack);

#endif