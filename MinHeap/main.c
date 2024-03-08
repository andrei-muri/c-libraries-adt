#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    int priority;
} NodeMinT;

typedef struct {
    int nbOfElements;
    int size;
    NodeMinT* array;
} PriorityQueueMin;

PriorityQueueMin* newPriorityQueue(int size) {
    PriorityQueueMin* queue = (PriorityQueueMin*)malloc(sizeof(PriorityQueueMin));
    if(queue) {
        queue->nbOfElements = 0;
        queue->size = size;
        queue->array = (NodeMinT*)calloc(size, sizeof(NodeMinT));
    }
    return queue;
}

NodeMinT createNode(char* name, int priority) {
    NodeMinT node;
    strcpy(node.name, name);
    node.priority = priority;
    return node;
}

void insert(PriorityQueueMin* queue, char* name, int priority);
void shiftUp(PriorityQueueMin* queue, int i);
NodeMinT dequeue(PriorityQueueMin* queue);
void shiftDown(PriorityQueueMin* queue, int i);
NodeMinT getMin(PriorityQueueMin* queue);
int parentIndex(int i);
int leftIndex(int i);
int rightIndex(int i);
void swap(NodeMinT* A, NodeMinT* B);

int main()
{
    PriorityQueueMin* queue = newPriorityQueue(15);
    insert(queue, "Muresan Andrei", 18);
    insert(queue, "Neghina Vlad", 17);
    insert(queue, "Craciunas Victor", 10);
    insert(queue, "Dorian", 9);
    insert(queue, "Mara", 11);

    NodeMinT min = dequeue(queue);
    printf("%s\n", min.name);

    min = dequeue(queue);
    printf("%s\n", min.name);
    min = dequeue(queue);
    printf("%s\n", min.name);
    min = dequeue(queue);
    printf("%s\n", min.name);
    min = dequeue(queue);
    printf("%s\n", min.name);

    insert(queue, "Felix", 20);
    min = dequeue(queue);
    printf("%s\n", min.name);
    return 0;
}

int parentIndex(int i) {return i>>1;};
int leftIndex(int i) {return i<<1;};
int rightIndex(int i) {return (i<<1) + 1;};

void swap(NodeMinT* A, NodeMinT* B) {
    NodeMinT temp = *A;
    *A = *B;
    *B = temp;
}

void insert(PriorityQueueMin* queue, char* name, int priority) {
    if(queue->nbOfElements + 1 >= queue->size) {
        queue->array = (NodeMinT*)realloc(queue->array, (queue->size + 5) * sizeof(NodeMinT));
        queue->size += 5;
    }
    queue->array[++queue->nbOfElements] = createNode(name, priority);
    shiftUp(queue, queue->nbOfElements);
}

void shiftUp(PriorityQueueMin* queue, int i) {
    if(i > queue->nbOfElements) return;
    if(i == 1) return;
    int parent = parentIndex(i);
    if(queue->array[i].priority < queue->array[parent].priority) {
        swap(&(queue->array[i]), &(queue->array[parent]));
        shiftUp(queue, parent);
    }
}

NodeMinT dequeue(PriorityQueueMin* queue) {
    NodeMinT temp = queue->array[1];
    swap(&(queue->array[1]), &(queue->array[queue->nbOfElements--]));
    shiftDown(queue, 1);
    return temp;
}

void shiftDown(PriorityQueueMin* queue, int i) {
    if(i >= queue->nbOfElements) return;

    int left = leftIndex(i);
    int right = rightIndex(i);
    int switchIndex = i;

    if(left <= queue->nbOfElements && queue->array[switchIndex].priority > queue->array[left].priority) {
        switchIndex = left;
    }

    if(right <= queue->nbOfElements && queue->array[switchIndex].priority > queue->array[right].priority) {
        switchIndex = right;
    }

    if(switchIndex != i) {
        swap(&(queue->array[i]), &(queue->array[switchIndex]));
        shiftDown(queue, switchIndex);
    }
}
