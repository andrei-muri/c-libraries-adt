#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stacks.h"

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(stack) {
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}

NodeT* createNode(int key) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        node->key = key;
        node->next = node->prev = NULL;
    }
    return node;
}

bool isEmpty(Stack* stack) {
    return !stack->count;
}

void push(Stack* stack, int key) {
    NodeT* node = createNode(key);
    if(node) {
        if(isEmpty(stack)) {
            node->prev = NULL;
        }  else {
            node->prev = stack->top;
            stack->top->next = node;
        }
        node->next = NULL;
        stack->top = node;
        stack->count++;
    }
}

NodeT* pop(Stack* stack) {
    if(isEmpty(stack)) {
        printf("Stack is empty. The el. returned will be NULL\n");
        return NULL;
    } else {
        NodeT* node= stack->top;
        stack->top = stack->top->prev;
        stack->count--;
        return node;
    }
}

void printContent(Stack* stack) {
    if(isEmpty(stack)) {
        printf("The stack is empty!\n");
    } else {
        NodeT* iterator = stack->top;
        while(iterator) {
            printf("----------\n");
            printf("|   %d   |\n", iterator->key);
            printf("----------\n");
            iterator = iterator->prev;
        }
    }
}

NodeT* top(Stack* stack) {
    if(isEmpty(stack)) {
        printf("Stack is empty. The el. returned will be NULL\n");
    }
    return stack->top;
}
