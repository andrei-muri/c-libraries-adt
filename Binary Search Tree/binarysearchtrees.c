#include <stdio.h>
#include <stdlib.h>
#include "binarysearchtrees.h"

BSTNodeT* createNode(int key) {
    BSTNodeT* node = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if(node) {
        node->key = key;
        node->left = node->right = NULL;
    }
    return node;
}

BSTNodeT* insert1(BSTNodeT* root, int key) {
    if(!root) {
        root = createNode(key);
    } else {
        if(root->key > key) {
            root->left = insert1(root->left, key);
        } else {
            root->right = insert1(root->right, key);
        }
    }
    return root;
}

void insert2(BSTNodeT** root, int key) {
    if(!(*root)) {
        *root = createNode(key);
    } else {
        if((*root)->key > key) {
            insert2(&((*root)->left), key);
        } else {
            insert2(&((*root)->right), key);
        }
    }
}

BSTNodeT* find(BSTNodeT* root, int key) {
    if(!root) {
        printf("The element %d is not in the tree!\n", key);
        return NULL;
    } else {
        if(root->key > key) {
            return find(root->left, key);
        } else if(root->key < key){
            return find(root->right, key);
        } else {
            return root;
        }
    }
}

BSTNodeT* findMin(BSTNodeT* root) {
    if(!root) {
        return NULL;
    }
    if(!root->left) {
        return root;
    } else {
        return findMin(root->left);
    }
}

BSTNodeT* findMax(BSTNodeT* root) {
    if(!root) {
        return NULL;
    }
    if(!root->right) {
        return root;
    } else {
        return findMax(root->right);
    }
}

int nbOfLeaves(BSTNodeT* root) {
    if(!root) {
        return 0;
    }
    if(!root->left && !root->right) {
        return 1;
    } else {
        return nbOfLeaves(root->left) + nbOfLeaves(root->right);
    }
}

void getHeight(BSTNodeT* root, int* height, int level) {
    if(!root) {
        return;
    }
    if(!root->right && !root->left) {
        if(level > *height) {
            *height = level;
        }
    } else {
        getHeight(root->left, height, level + 1);
        getHeight(root->right, height, level + 1);
    }
}

BSTNodeT* deleteNode(BSTNodeT* root, int key) {
    if(!root) {
        printf("Element %d not found!\n", key);
    } else if(root->key > key){
        root->left = deleteNode(root->left, key);
    } else if(root->key < key) {
        root->right = deleteNode(root->right, key);
    } else {
        if(root->left && root->right) {
            BSTNodeT* min = findMin(root->right);
            root->key = min->key;
            root->right = deleteNode(root->right, min->key);
        } else {
            BSTNodeT* temp = root;
            if(root->left) {
                root = root->left;
            } else if(root->right){
                root = root->right;
            } else if(!root->right && !root->left) {
                root = NULL;
            }
            free(temp);
        }
    }
    return root;
}

void print(BSTNodeT* iterator) {
    if(iterator) {
        print(iterator->left);
        printf("%d ", iterator->key);
        print(iterator->right);
    }
}
