#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* next;
    struct node* prev;
}NodeT;

typedef struct {
    int count;
    NodeT* top;
} Stack;

Stack* createStack();
NodeT* createNode(int key);
bool isEmpty(Stack* stack);
void push(Stack* stack, int key);
NodeT* pop(Stack* stack);
void printContent(Stack* stack);
NodeT* top(Stack* stack);


#endif // STACK_H_INCLUDED
