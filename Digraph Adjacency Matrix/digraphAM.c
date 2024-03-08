//
// Created by Muri on 5/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "digraphAM.h"

extern GraphT* createGraph(int nbOfNodes) {
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

extern void addEdge(GraphT* graph, int from, int to) {
    if(!graph) {
        printf("Graph non-existent!\n");
        return;
    } else if(from >= graph->nbOfNodes || to >= graph->nbOfNodes) {
        printf("Nodes out of bounds!\n");
        return;
    } else if(graph->matrix[from][to]) {
        printf("Edge (%d, %d) already existent", from, to);
        return;
    }
    graph->matrix[from][to] = true;
}

extern bool hasEdge(GraphT* graph, int from, int to) {
    if(!graph) {
        printf("Graph non-existent!\n");
        return false;
    } else if(from >= graph->nbOfNodes || to >= graph->nbOfNodes) {
        printf("Nodes out of bounds!\n");
        return false;
    }
    return graph->matrix[from][to];
}

extern void print(GraphT* graph) {
    if(!graph) {
        printf("Graph non-existent!\n");
        return;
    }
    for(int i = 0; i < graph->nbOfNodes; i++) {
        for(int j = 0; j < graph->nbOfNodes; j++) {
            if(graph->matrix[i][j]) {
                printf("{%d -> %d}\n", i, j);
            }
        }
    }
}

extern GraphT* purge(GraphT* graph) {
    if(graph) {
        free(graph);
    }
    return NULL;
}