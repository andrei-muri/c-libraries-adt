//
// Created by Muri on 5/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xorlist.h"

ListT* newList() {
    ListT* list = (ListT*)malloc(sizeof(ListT));
    if(list) {
        list->count = 0;
        list->first = list->last = NULL;
    }
    return list;
}

NodeT* createNode(int key) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        node->key = key;
        node->link = (NodeT*)0x0;
    }
    return node;
}

bool isEmpty(ListT* list) {
    return !list->count;
}

void append(ListT* list, int key) {
    NodeT* node = createNode(key);
    if(node) {
        if(isEmpty(list)) {
            list->first = node;
            node->link = (NodeT*)0x0;
        } else {
            node->link = list->last;
            list->last->link = (NodeT*)((uintptr_t)(node) ^ (uintptr_t)(list->last->link));
        }
        list->count++;
        list->last = node;
    }
}

void print(ListT* list) {
    NodeT* p = list->first;
    NodeT* q = (NodeT*)0x0;
    NodeT* next = list->first;

    printf("NULL->");
    while(next) {
        printf("%d->", p->key);
        next = (NodeT*)((uintptr_t)(q) ^ (uintptr_t)(p->link));
        q = p;
        p = next;
    }
    printf("NULL\n");
}