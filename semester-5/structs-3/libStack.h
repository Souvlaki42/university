#ifndef STACK_H
#define STACK_H

// Στατική στοίβα με χρήση πίνακα
typedef struct {
  int *start;
  int size;
  int cap;
} Stack;

void stack_init(Stack *stack, int cap);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);

// Δυναμική στοίβα με χρήση συνδεδεμένης λίστας
typedef struct node {
  int value;
  struct node *next;
} Node;

void dstack_init(Node **stack);
void dstack_push(Node **stack, int value);
int dstack_pop(Node **stack);

// Στατική ουρά με χρήση πίνακα
typedef struct {
  int *items;
  int start;
  int end;
  int cap;
} Queue;

void queue_init(Queue *queue, int cap);
void queue_push(Queue *queue, int value);
int queue_pop(Queue *queue);

#endif