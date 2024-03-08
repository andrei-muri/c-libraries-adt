#include <stdio.h>
#include <stdlib.h>
#include "binarytrees.h"

void fatalError(const char* msg) {
    printf("%s", msg);
    exit(1);
}

BTNodeT* createBTNode(char key) {
    BTNodeT* node = (BTNodeT*)malloc(sizeof(BTNodeT));
    if(node) {
        node->key = key;
        node->left = node->right = NULL;
    }
    return node;
}

BTNodeT* createBinTree(FILE* input) {
    char key;
    fscanf(input, "%c", &key);
    if(key == '*') {
        return NULL;
    }
    BTNodeT* node = createBTNode(key);
    if(!node) {
        fatalError("Out of memory in binary tree");
    }
    node->left = createBinTree(input);
    node->right = createBinTree(input);
    return node;
}

int nbOfLeaves(BTNodeT* root) {
    if(!root) {
        return 0;
    }
    if(!root->left && !root->right) {
        return 1;
    } else {
        return nbOfLeaves(root->left) + nbOfLeaves(root->right);
    }
}

void getHeight(BTNodeT* root, int* height, int level) {
    if(!root) {
        return;
    }
    if(!root->left && !root->right) {
        if(level > *height) {
            *height = level;
        }
    } else {
        getHeight(root->left, height, level + 1);
        getHeight(root->right, height, level + 1);
    }
}

void printPreorder(BTNodeT* iterator) {
    if(iterator) {
        printf("%c", iterator->key);
        printPreorder(iterator->left);
        printPreorder(iterator->right);
    }
}

void printInorder(BTNodeT* iterator) {
    if(iterator) {
        printInorder(iterator->left);
        printf("%c", iterator->key);
        printInorder(iterator->right);
    }
}

void printPostOrder(BTNodeT* iterator) {
    if(iterator) {
        printPostOrder(iterator->left);
        printPostOrder(iterator->right);
        printf("%c", iterator->key);
    }
}
