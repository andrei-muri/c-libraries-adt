#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queues.h"

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(queue) {
        queue->count = 0;
        queue->front = queue->rear = NULL;
    }
    return queue;
}

NodeT* createNode(int key) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        node->key = key;
        node->next = NULL;
    }
    return node;
}

bool isEmpty(Queue* queue) {
    return !queue->count;
}

void enqueue(Queue* queue, int key) {
    NodeT* node = createNode(key);
    if(node) {
        if(isEmpty(queue)) {
            queue->front = node;
            node->next = NULL;
        } else {
            node->next = queue->rear;
        }
        queue->rear = node;
        queue->count++;
    }
}

NodeT* dequeue(Queue* queue) {
    if(isEmpty(queue)) {
        printf("Queue is empty!\n");
        return NULL;
    } else if(queue->rear == queue->front) {
        NodeT* temp = queue->rear;
        queue->rear = queue->front = NULL;
        queue->count--;
        return temp;
    } else {
        NodeT* temp = queue->front;
        NodeT* iterator = queue->rear;
        while(iterator->next != queue->front) {
            iterator = iterator->next;
        }
        queue->front = iterator;
        queue->front->next = NULL;
        queue->count--;
        return temp;
    }
}

NodeT* front(Queue* queue) {
    if(isEmpty(queue)) {
        printf("Queue is empty!\n");
    }
    return queue->front;
}

NodeT* rear(Queue* queue) {
    if(isEmpty(queue)) {
        printf("Queue is empty!\n");
    }
    return queue->rear;
}

int numberOfItems(Queue* queue) {
    return queue->count;
}

void printContent(Queue* queue) {
    if(isEmpty(queue)) {
        printf("Queue is empty!\n");
    } else {
        NodeT* iterator = queue->rear;
        while(iterator) {
            printf("(%d)->", iterator->key);
            iterator = iterator->next;
        }
        printf("NULL\n");
    }
}
