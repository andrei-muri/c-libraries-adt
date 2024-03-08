#ifndef AVLTREES_H_INCLUDED
#define AVLTREES_H_INCLUDED
typedef struct node {
    int key;
    int balance;
    struct node* left;
    struct node* right;
} AVLNodeT;

extern AVLNodeT* createNode(int key);
extern int height(AVLNodeT* root);
extern AVLNodeT* insert(AVLNodeT* root, int key);
extern void setBalances(AVLNodeT* iterator);
extern AVLNodeT* findMin(AVLNodeT* iterator);
extern AVLNodeT* deleteNode(AVLNodeT* root, int key);
extern void print(AVLNodeT* iterator);

#endif // AVLTREES_H_INCLUDED
