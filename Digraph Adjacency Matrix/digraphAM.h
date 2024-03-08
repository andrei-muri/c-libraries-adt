//
// Created by Muri on 5/10/2023.
//

#ifndef DIGRAPHADJACENCYMATRIX_DIGRAPHAM_H
#define DIGRAPHADJACENCYMATRIX_DIGRAPHAM_H

#include <stdbool.h>

typedef struct {
    int nbOfNodes;
    bool** matrix;
} GraphT;

extern GraphT* createGraph(int nbOfNodes);
extern void addEdge(GraphT* graph, int from, int to);
extern bool hasEdge(GraphT* graph, int from, int to);
extern void print(GraphT* graph);
extern GraphT* purge(GraphT* graph);

#endif //DIGRAPHADJACENCYMATRIX_DIGRAPHAM_H
