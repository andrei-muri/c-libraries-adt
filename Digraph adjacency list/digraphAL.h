//
// Created by Muri on 5/10/2023.
//

#ifndef DIGRAPHADJACENCYLIST_DIGRAPHAL_H
#define DIGRAPHADJACENCYLIST_DIGRAPHAL_H
#include <stdbool.h>

typedef struct node {
    int key;
    struct node* next;
} NodeT;

typedef struct {
    int nbOfNodes;
    NodeT** list;
} GraphT;

extern GraphT* createGraph(int nbOfNodes);
extern void addEdge(GraphT* graph, int from, int to);
static void append(NodeT** head, int key);
extern bool hasEdge(GraphT* graph, int from, int to);
extern void print(GraphT* graph);
extern GraphT* purge(GraphT* graph);

static NodeT* createNode(int key);
static bool isEmpty(NodeT* head);
static bool find(NodeT* head, int key);
#endif //DIGRAPHADJACENCYLIST_DIGRAPHAL_H
