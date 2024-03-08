#include <stdio.h>
#include <stdlib.h>
#include "avltrees.h"

extern AVLNodeT* createNode(int key) {
    AVLNodeT* node = (AVLNodeT*)malloc(sizeof(AVLNodeT));
    if(node) {
        node->key = key;
        node->balance = 0;
        node->right = node->left = NULL;
    }
    return node;
}

extern int height(AVLNodeT* root) {
    if(root == NULL) {
        return -1;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight) {
            return (leftHeight + 1);
        } else {
            return (rightHeight + 1);
        }
    }
}

static int getRotation(AVLNodeT* root) {
    //returns which rotation needs to be performed
    //according to the AVL algorithm
    if(root->balance > 1) {
        int heightLeft = height(root->left->left);
        int heightRight = height(root->left->right);
        if(heightLeft > heightRight) {
            return 0; //LL rotation
        } else {
            return 1; //LR rotation
        }
    } else if(root->balance < -1) {
        int heightLeft = height(root->right->left);
        int heightRight = height(root->right->right);
        if(heightLeft > heightRight) {
            return 2; //RL rotation
        } else {
            return 3; //RR rotation
        }
    }
    return -1;
}

static AVLNodeT* LLrotation(AVLNodeT* A) {
    AVLNodeT* temp = A;
    A = temp->left;
    temp->left = A->right;
    A->right = temp;
    return A;
}

static AVLNodeT* LRrotation(AVLNodeT* A) {
    AVLNodeT* temp = A;
    AVLNodeT* temp2 = temp->left;
    A = temp->left->right;
    temp->left = A->right;
    temp2->right = A->left;
    A->left = temp2;
    A->right = temp;
    return A;
}

static AVLNodeT* RLrotation(AVLNodeT* A) {
    AVLNodeT* temp = A;
    AVLNodeT* temp2 = temp->right;
    A = temp->right->left;
    temp->right = A->left;
    temp2->left = A->right;
    A->left = temp;
    A->right = temp2;
    return A;
}

static AVLNodeT* RRrotation(AVLNodeT* A) {
    AVLNodeT* temp = A;
    A = temp->right;
    temp->right = A->left;
    A->left = temp;
    return A;
}

static AVLNodeT* balance(AVLNodeT* root) {
    int rotation = getRotation(root);
    switch(rotation) {
        case 0: //LL rotation
            return LLrotation(root);
        case 1: //LR rotation
            return LRrotation(root);
        case 2: //RL rotation
            return RLrotation(root);
        case 3: //RR rotation
            return RRrotation(root);
        default:
            return NULL;
    }
}

extern AVLNodeT* insert(AVLNodeT* root, int key) {
    //the same as in bst but checks for unbalances
    if(root && root->key == key) {
        printf("Node already in tree!");
    } else if(!root) {
        root = createNode(key);
    } else {
        if(root->key > key) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        //if the root is unbalanced, balance it
        root->balance = height(root->left) - height(root->right);
        if(root->balance < -1 || root->balance > 1) {
            return balance(root);
        }
    }
    return root;
}

extern void setBalances(AVLNodeT* iterator) {
    if(iterator) {
        iterator->balance = height(iterator->left) - height(iterator->right);
        setBalances(iterator->left);
        setBalances(iterator->right);
    }
}

extern AVLNodeT* findMin(AVLNodeT* iterator) {
    while(iterator->left) {
        iterator = iterator->left;
    }
    return iterator;
}

extern AVLNodeT* deleteNode(AVLNodeT* root, int key) {
    //it is the same as the bst delete algorithm
    //but after you finish deletion, you recalculate the balances
    //because they got disrupted and if the node is not
    //balanced, balance it and return it
    if(!root) {
        printf("Node not found!\n");
    } else if(root->key > key) {
        root->left = deleteNode(root->left, key);
    } else if(root->key < key) {
        root->right = deleteNode(root->right, key);
    } else {
        if(root->left && root->right) {
            AVLNodeT* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        } else {
            AVLNodeT* temp = root;
            if(root->right) {
                root = root->right;
            } else if(root->left) {
                root = root->left;
            } else {
                root = NULL;
            }
            free(temp);
        }
    }
    if(!root) {
        return NULL;
    }
    setBalances(root); // set the balances because they got disrupted
    if(root->balance < -1 || root->balance > 1) {
        //if the node is not balanced, rebalance it
        return balance(root);
    }
    return root;
}

extern void print(AVLNodeT* iterator) {
    if(iterator) {
        print(iterator->left);
        printf("(Node: %d, Balance: %d)\n", iterator->key, iterator->balance);
        print(iterator->right);
    }
}
