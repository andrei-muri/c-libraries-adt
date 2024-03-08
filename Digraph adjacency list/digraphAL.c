//
// Created by Muri on 5/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "digraphAL.h"

extern GraphT* createGraph(int nbOfNodes) {
    GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    if(graph) {
        graph->nbOfNodes = nbOfNodes;
        graph->list = (NodeT**)calloc(sizeof(NodeT*), nbOfNodes);
    }
    return graph;
}

extern void addEdge(GraphT* graph, int from, int to) {
    if(!graph) {
        printf("Graph is non-existent!\n");
        return;
    } else if(from >= graph->nbOfNodes || to >= graph->nbOfNodes) {
        printf("Nodes out of bounds!\n");
    } else if(find(graph->list[from], to)){
        printf("Edge {%d->%d} already existent!n", from, to);
        return;
    }
    append(&(graph->list[from]), to);
}

extern void print(GraphT* graph) {
    if(!graph) {
        printf("Graph is non-existent!\n");
        return;
    }
    NodeT* iterator;
    for(int i = 0; i < graph->nbOfNodes; i++) {
        printf("%d->", i);
        iterator = graph->list[i];
        while(iterator) {
            printf("%d->", iterator->key);
            iterator = iterator->next;
        }
        printf("NULL\n");
    }
}

extern GraphT* purge(GraphT* graph) {
    if(graph) {
        free(graph);
    }
    return NULL;
}

extern bool hasEdge(GraphT* graph, int from, int to) {
    return find(graph->list[from], to);
}

//

static NodeT* createNode(int key) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        node->key = key;
        node->next = NULL;
    }
    return node;
}

static bool isEmpty(NodeT* head) {
    return (head == NULL);
}


static void append(NodeT** head, int key) {
    NodeT* node = createNode(key);
    if(isEmpty(*head)) {
        *head = node;
    } else {
        NodeT* iterator = *head;
        while(iterator->next) {
            iterator = iterator->next;
        }
        iterator->next = node;
    }
    node->next = NULL;
}

static bool find(NodeT* head, int key) {
    NodeT* iterator = head;
    while(iterator && iterator->key != key) {
        iterator = iterator->next;
    }
    return (iterator != NULL);
}

