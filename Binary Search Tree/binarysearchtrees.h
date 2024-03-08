#ifndef BINARYSEARCHTREES_H_INCLUDED
#define BINARYSEARCHTREES_H_INCLUDED
typedef struct node {
    int key;
    struct node* left;
    struct node* right;
}BSTNodeT;

BSTNodeT* createNode(int key);
BSTNodeT* insert1(BSTNodeT* root, int key);
void insert2(BSTNodeT** root, int key);
BSTNodeT* find(BSTNodeT* root, int key);
BSTNodeT* findMin(BSTNodeT* root);
BSTNodeT* findMax(BSTNodeT* root);
int nbOfLeaves(BSTNodeT* root);
void getHeight(BSTNodeT* root, int* height, int level);
BSTNodeT* deleteNode(BSTNodeT* root, int key);
void print(BSTNodeT* iterator);

#endif // BINARYSEARCHTREES_H_INCLUDED
