#ifndef DLLIST_H_INCLUDED
#define DLLIST_H_INCLUDED
#include <stdbool.h>
typedef struct node {
    int key;
    struct node* next;
    struct node* prev;
}NodeT;

typedef struct {
    int count;
    NodeT* first;
    NodeT* last;
}DLList;

DLList* createDLList();
NodeT* createNode(int key);
bool isEmpty(DLList* list);
NodeT* findNode(DLList* list, int key);
void insert(DLList* list, int key);
void append(DLList* list, int key);
void insertSorted(DLList* list, int key);
void insertBefore(DLList* list, int givenKey, int key);
void insertAfter(DLList* list, int givenKey, int key);
void printList(DLList* list);
void deleteElement(DLList* list, int key);
void emptyList(DLList* list);
DLList* deleteList(DLList* list);
void sortList(DLList* list);
#endif // DLLIST_H_INCLUDED
