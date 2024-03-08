//
// Created by Muri on 5/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphAM.h"

GraphT* createGraph(int nbOfNodes) {
    GraphT* graph = (GraphT*)malloc(sizeof(GraphT));
    if(graph) {
        graph->nbOfNodes = nbOfNodes;

        graph->matrix = (bool**)calloc(sizeof(bool*), nbOfNodes);
        for(int i = 0; i < nbOfNodes; i++) {
            graph->matrix[i] = (bool*)calloc(sizeof(bool), nbOfNodes);
        }
    }
    return graph;
}

void addEdge(GraphT* graph, int A, int B) {
    if(A >= graph->nbOfNodes || B >= graph->nbOfNodes) {
        printf("Edge out of bounds!\n");
        return;
    } else if(graph->matrix[A][B]) {
        printf("Edges (%d, %d) and (%d, %d) already present!\n", A, B, B, A);
        return;
    }
    graph->matrix[A][B] = true;
    graph->matrix[B][A] = true;
}

bool hasEdge(GraphT* graph, int A, int B) {
    if(!graph->matrix) {
        return false;
    } else if(A >= graph->nbOfNodes || B >= graph->nbOfNodes) {
        printf("Edge non-existent!\n");
        return false;
    }
    return graph->matrix[A][B];
}

void printGraph(GraphT* graph) {
    if(!graph->matrix) {
        printf("Graph is non-existent!\n");
        return;
    } else if(!graph->matrix) {
        printf("Graph has no adjacency matrix!\n");
        return;
    }
    int nodes = graph->nbOfNodes;
    bool isEmpty = true;
    int i, j;
    for(i = 0;  i < nodes; i++) {
        for(j = 0; i - j > 0; j++) {
            if(graph->matrix[i][j]) {
                printf("(%d, %d)\n", i, j);
                isEmpty = false;
            }
        }
    }
    if(isEmpty) {
        printf("Graph is empty!\n");
    }
}

void destroyGraph(GraphT* graph) {
    if(graph && graph->matrix) {
        for(int i = 0; i < graph->nbOfNodes; i++) {
            free(graph->matrix[i]);
        }
        free(graph->matrix);
        graph->matrix = NULL;
    }
}

GraphT* purgeGraph(GraphT* graph) {
    if(graph) {
        free(graph);
    }
    return NULL;
}