#ifndef SLLIST_H_INCLUDED
#define SLLIST_H_INCLUDED
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* next;
} NodeT;

typedef struct {
    int count;
    NodeT* first;
    NodeT* last;
} SLList;

extern SLList* createList();
extern NodeT* createNode(int key);
extern bool isEmpty(SLList* list);
extern void insertSorted(SLList* list, int key);
extern void insert(SLList* list, int key);
extern void append(SLList* list, int key);
extern void insertAfterKey(SLList* list, int givenKey, int key);
extern void insertBeforeKey(SLList* list, int givenKey, int key);
extern NodeT* findElement(SLList* list, int key);
extern void deleteElement(SLList* list, int key);
extern void emptyList(SLList* list);
extern NodeT* deleteList(SLList* list);
extern void sortList(SLList* list);
extern void printList(SLList* list);

#endif // SLLIST_H_INCLUDED
