//
// Created by Muri on 5/10/2023.
//

#ifndef XORLIST_XORLIST_H
#define XORLIST_XORLIST_H
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* link;
} NodeT;

typedef struct {
    int count;
    NodeT* first;
    NodeT* last;
} ListT;

ListT* newList();
NodeT* createNode(int key);
bool isEmpty(ListT* list);
void append(ListT* list, int key);
void print(ListT* list);
#endif //XORLIST_XORLIST_H
