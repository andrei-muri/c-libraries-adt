#ifndef QUEUES_H_INCLUDED
#define QUEUES_H_INCLUDED
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* next;
}NodeT;

typedef struct {
    int count;
    NodeT* front;
    NodeT* rear;
}Queue;

Queue* createQueue();
bool isEmpty(Queue* queue);
void enqueue(Queue* queue, int key);
NodeT* dequeue(Queue* queue);
NodeT* front(Queue* queue);
NodeT* rear(Queue* queue);
int numberOfItems(Queue* queue);
void printContent(Queue* queue);


#endif // QUEUES_H_INCLUDED
