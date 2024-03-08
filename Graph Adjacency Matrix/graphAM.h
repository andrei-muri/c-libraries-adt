//
// Created by Muri on 5/10/2023.
//

#ifndef GRAPHADJACENCYMATRIX_GRAPHAM_H
#define GRAPHADJACENCYMATRIX_GRAPHAM_H
#include <stdbool.h>

typedef struct {
    int nbOfNodes;
    bool** matrix;
} GraphT;

GraphT* createGraph(int nbOfNodes);
void addEdge(GraphT* graph, int A, int B);
bool hasEdge(GraphT* graph, int A, int B);
void printGraph(GraphT* graph);
void destroyGraph(GraphT* graph);
GraphT* purgeGraph(GraphT* graph);

#endif //GRAPHADJACENCYMATRIX_GRAPHAM_H
