#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//priority queue implementation using a max heap

typedef struct {
    char name[30];
    int priority;
} NodeMaxT;

typedef struct {
    int nbOfElements;
    int size;
    NodeMaxT* array;
} PriorityQueueMax;

NodeMaxT createNode(char* name, int priority) {
    NodeMaxT node;
    strcpy(node.name, name);
    node.priority = priority;
    return node;
}

PriorityQueueMax* newPriorityQueue(int size) {
    PriorityQueueMax* queue = (PriorityQueueMax*)malloc(sizeof(PriorityQueueMax));
    if(queue) {
        queue->nbOfElements = 0;
        queue->size = size;
        queue->array = (NodeMaxT*)calloc(size, sizeof(NodeMaxT));
    }
    return queue;
}

int parentIndex(int i) {return i>>1;}
int leftIndex(int i) {return i<<1;}
int rightIndex(int i) {return (i<<1) + 1;}

void swapNode(NodeMaxT* A, NodeMaxT* B) {
    NodeMaxT temp;
    temp = *A;
    *A = *B;
    *B = temp;
}


void shiftUp(PriorityQueueMax* queue, int i) {
    if(i > queue->nbOfElements) return;
    if(i == 1) return;
    if(queue->array[i].priority > queue->array[parentIndex(i)].priority) {
        swapNode(&(queue->array[i]), &(queue->array[parentIndex(i)]));
        shiftUp(queue, parentIndex(i));
    }
}
void insert(PriorityQueueMax* queue, char* name, int priority) {
    if(queue->nbOfElements + 1 >= queue->size) {
        NodeMaxT* temp = (NodeMaxT*)realloc(queue->array, (queue->size + 5) * sizeof(NodeMaxT));
        if(temp) {
            queue->array = temp;
            queue->size += 5;
        } else {
            printf("Realloc failed!");
        }
    }
    queue->array[++queue->nbOfElements] = createNode(name, priority);
    shiftUp(queue, queue->nbOfElements);
}

void shiftDown(PriorityQueueMax* queue, int i) {
    if(i > queue->nbOfElements) return;

    int maxIndex = i;
    int left = leftIndex(i);
    int right = rightIndex(i);

    if(left <= queue->nbOfElements && queue->array[left].priority > queue->array[maxIndex].priority) {
        maxIndex = left;
    }
    if(right <= queue->nbOfElements && queue->array[right].priority > queue->array[maxIndex].priority) {
        maxIndex = right;
    }
    if(i != maxIndex) {
        swapNode(&(queue->array[i]), &(queue->array[maxIndex]));
        shiftDown(queue, maxIndex);
    }
}
NodeMaxT dequeue(PriorityQueueMax* queue) {
    if(queue->nbOfElements == 1) return queue->array[1];
    NodeMaxT temp = queue->array[1];
    swapNode(&(queue->array[1]), &(queue->array[queue->nbOfElements--]));
        shiftDown(queue, 1);
    return temp;
}


int main()
{
    PriorityQueueMax* queue = newPriorityQueue(10);
    insert(queue, "Felix", 10);
    insert(queue, "Muri", 14);
    insert(queue, "Victor", 7);
    insert(queue, "Saipi", 20);
    insert(queue, "Vlad", 1);
    NodeMaxT maxim = dequeue(queue);
    printf("%s\n", maxim.name);
    maxim = dequeue(queue);
    printf("%s\n", maxim.name);
    return 0;
}
