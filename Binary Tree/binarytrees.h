#ifndef BINARYTREES_H_INCLUDED
#define BINARYTREES_H_INCLUDED
typedef struct node {
    char key;
    struct node* left;
    struct node* right;
} BTNodeT;

void fatalError(const char* msg);
BTNodeT* createBTNode(char key);
BTNodeT* createBinTree(FILE* input);
int nbOfLeaves(BTNodeT* root);
void getHeight(BTNodeT* root, int* height, int level);
void printPreorder(BTNodeT* iterator);
void printInorder(BTNodeT* iterator);
void printPostOrder(BTNodeT* iterator);

#endif // BINARYTREES_H_INCLUDED
