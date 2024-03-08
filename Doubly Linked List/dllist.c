#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dllist.h"

DLList* createDLList() {
    DLList* newList = (DLList*)malloc(sizeof(DLList));
    if(newList) {
        newList->count = 0;
        newList->first = newList->last = NULL;
    }
    return newList;
}

NodeT* createNode(int key) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if(newNode) {
        newNode->key = key;
        newNode->next = newNode->prev = NULL;
    }
    return newNode;
}

bool isEmpty(DLList* list) {
    return !list->count;
}

NodeT* findNode(DLList* list, int key) {
    NodeT* iterator = list->first;
    while(iterator && iterator->key != key) {
        iterator = iterator->next;
    }
    return iterator;
}

void insert(DLList* list, int key) {
    NodeT* newNode = createNode(key);
    if(newNode){
        if(isEmpty(list)) {
            list->last = newNode;
            newNode->next = NULL;
        } else {
            newNode->next = list->first;
            list->first->prev = newNode;
        }
        list->first = newNode;
        newNode->prev = NULL;
        list->count++;
    }
}

void append(DLList* list, int key) {
    NodeT* newNode = createNode(key);
    if(newNode) {
        if(isEmpty(list)) {
            list->first = newNode;
            newNode->prev = NULL;
        } else {
            newNode->prev = list->last;
            list->last->next = newNode;
        }
        list->last = newNode;
        newNode->next = NULL;
        list->count++;
    }
}

void insertSorted(DLList* list, int key) {
    NodeT* iterator = list->first;
    while(iterator && iterator->key < key) {
            iterator = iterator->next;
    }
    if(!iterator) {
        append(list, key);
    }else{
        insertBefore(list, iterator->key , key);
    }
}

void insertBefore(DLList* list, int givenKey, int key) {
    if(isEmpty(list)) {
        printf("List is empty! The element will still be added\n");
        insert(list, key);
    } else {
        NodeT* node = findNode(list, givenKey);
        if(!node || node == list->first) {
            if(!node) {
                printf("Couldn't find the node %d!\n. The new el. will be inserted in the list!\n", givenKey);
            }
            insert(list, key);
        } else {
            NodeT* newNode = createNode(key);
            if(newNode) {
                newNode->prev = node->prev;
                newNode->next = node;
                node->prev->next = newNode;
                node->prev = newNode;
                list->count++;
            }
        }
    }
}

void insertAfter(DLList* list, int givenKey, int key) {
    if(isEmpty(list)) {
        printf("List is empty! The element will still be added\n");
        insert(list, key);
    } else {
        NodeT* node = findNode(list, givenKey);
        if(!node || node == list->last) {
            if(!node) {
                printf("Couldn't find the node %d!\n. The new el. will be appended to the list!\n", givenKey);
            }
            append(list, key);
        } else {
            NodeT* newNode = createNode(key);
            if(newNode) {
                newNode->next = node->next;
                newNode->prev = node;
                node->next = newNode;
                node->next->prev = newNode;
                list->count++;
            }
        }
    }
}

void printList(DLList* list) {
    if(isEmpty(list)) {
        printf("List is empty!\n");
    } else {
        NodeT* iterator = list->first;
        while(iterator) {
            printf("(%d)->", iterator->key);
            iterator = iterator->next;
        }
        printf("NULL\n");
    }
}

void deleteElement(DLList* list, int key) {
    NodeT* node = findNode(list, key);
    if(!node) {
        printf("Element %d non-existent!\n", key);
    } else {
        if(node == list->first) {
            list->first = list->first->next;
            list->first->prev = NULL;
        } else if(node == list->last) {
            list->last = list->last->prev;
            list->last->next = NULL;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        list->count--;
        free(node);
    }
}

void emptyList(DLList* list) {
    NodeT* iterator = list->first;
    NodeT* temp;
    while(iterator) {
        temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
    list->count = 0;
    list->first = NULL;
    list->last = NULL;
}

DLList* deleteList(DLList* list) {
    emptyList(list);
    free(list);
    return NULL;
}

void sortList(DLList* list) {
    NodeT* iterator1;
    NodeT* iterator2;
    int i, j;
    for(i = 0, iterator1 = list->first; i < list->count - 1; i++, iterator1 = iterator1->next) {
        for(j = i + 1, iterator2 = iterator1->next; j < list->count; j++, iterator2 = iterator2->next) {
            if(iterator1->key > iterator2->key) {
                int temp = iterator1->key;
                iterator1->key = iterator2->key;
                iterator2->key  = temp;
            }
        }
    }
}
