#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sllist.h"

extern SLList* createList() {
    SLList* newList = (SLList*) malloc(sizeof(SLList));
    if(newList) {
       newList->count = 0;
       newList->first = newList->last = NULL;
    }
    return newList;
}

extern NodeT* createNode(int key) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if(newNode) {
        newNode->key = key;
        newNode->next = NULL;
    }
    return newNode;
}

extern bool isEmpty(SLList* list) {
    return !list->count;
}

extern void insertSorted(SLList* list, int key) {
    NodeT* iterator = list->first;
    while(iterator && iterator->key < key) {
        iterator = iterator->next;
    }
    if(!iterator) {
        append(list, key);
    } else {
        insertBeforeKey(list, iterator->key, key);
    }
}

extern void insert(SLList* list, int key) {
    NodeT* newNode = createNode(key);
    if(newNode) {
        if(isEmpty(list)) {
            list->last = newNode;
            newNode->next = NULL;
        } else {
            newNode->next = list->first;
        }
        list->first = newNode;
        newNode->key = key;
        list->count++;
    }
}

extern void append(SLList* list, int key) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    if(newNode) {
        if(isEmpty(list)) {
            list->first = newNode;
        } else {
            list->last->next = newNode;
        }
        list->last = newNode;
        newNode->key = key;
        newNode->next = NULL;
        list->count++;
    }
}

extern NodeT* findElement(SLList* list, int key) {
    NodeT* iterator = list->first;
    while(iterator && iterator->key != key) {
        iterator = iterator->next;
    }
    if(!iterator) {
        printf("The node with the key %d could not be found.\n", key);
    }
    return iterator;
}

extern void insertAfterKey(SLList* list, int givenKey, int key) {
    if(isEmpty(list)) {
        printf("List is empty, so the element with the key %d"
               "could not be found! The element will be the only one in the list\n", key);
        insert(list, key);
        return;
    } else {
        NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
        if(newNode) {
            NodeT* iterator = findElement(list, givenKey);/*list->first*/;
            //while(iterator != NULL && iterator->key != givenKey) {
             //   iterator = iterator->next;
            //}
            if(!iterator || iterator == list->last) {
                if(!iterator) {
                    printf("The new element %d will be appended to the list!\n", givenKey);
                }
                append(list, key);
                return;
            }
            newNode->next = iterator->next;
            iterator->next = newNode;
            newNode->key = key;
            list->count++;
        }
    }
}

extern void insertBeforeKey(SLList* list, int givenKey, int key) {
    if(isEmpty(list)) {
        printf("List is empty, so the element with the key %d"
               "could not be found! The element will be the only one in the list\n", givenKey);
        insert(list, key);
        return;
    } else {
        NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
        if(newNode) {
            NodeT* iteratorPrev = NULL;
            NodeT* iterator = list->first;
            while(iterator != NULL && iterator->key != givenKey  ) {
                iteratorPrev = iterator;
                iterator = iterator->next;
            }
            if(!iterator || list->first == iterator) {
                if(!iterator) {
                printf("The element with the key %d could not be found "
                       "The new element will be inserted in the list!\n", givenKey);
                }
                insert(list, key);
                return;
            }
            iteratorPrev->next = newNode;
            newNode->next = iterator;
            newNode->key = key;
            list->count++;
        }
    }
}


extern void deleteElement(SLList* list, int key) {
    if(isEmpty(list)) {
        printf("The list is empty!\n");
    } else {
        NodeT* iteratorPrev = NULL;
        NodeT* iterator = list->first;
        while(iterator->key != key && iterator) {
            iteratorPrev = iterator;
            iterator = iterator->next;
        }
        if(!iterator) {
            printf("The node with the key %d could not be found.\n", key);
        } else {
            if(iterator == list->first) {
                list->first = list->first->next;
            } else if(iterator == list->last) {
                list->last = iteratorPrev;
                iteratorPrev->next = NULL;
            } else {
                iteratorPrev->next = iterator->next;
                iterator->next = NULL;
            }
            list->count--;
            free(iterator);
        }
    }
}

extern void emptyList(SLList* list) {
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

extern SLList* deleteList(SLList* list) {
    emptyList(list);
    free(list);
    return NULL;
}

extern void sortList(SLList* list) {
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

extern void printList(SLList* list) {
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
