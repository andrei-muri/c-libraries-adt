#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[40];
    int age;
    struct node* left;
    struct node* right;
} NodeT;

NodeT** createHashTable(int nbOfCells) {
    NodeT** BucketList = (NodeT**)calloc(nbOfCells, sizeof(NodeT*));
    for(int i = 0; i < nbOfCells; i++) {
        BucketList[i] = NULL;
    }
    return BucketList;
}

int hash(char* key) {
    int hashCode = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        hashCode = (int)key[i] * i + hashCode * i;
    }
    return hashCode % 17;
}

NodeT* createNode(char* name, int age) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        strcpy(node->name, name);
        node->age = age;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

NodeT* insertInBST(NodeT* root, char* key, int value) {
    if(!root) {
        root = createNode(key, value);
    } else {
        if(strcmp(root->name, key) > 0) {
            root->left = insertInBST(root->left, key, value);
        } else if(strcmp(root->name, key) < 0) {
            root->right = insertInBST(root->right, key, value);
        } else {
            printf("Key %s already existent!\n", key);
        }
    }
    return root;
}

void insert(NodeT** BucketList, char* key, int value) {
    int index = hash(key);
    BucketList[index] = insertInBST(BucketList[index], key, value);
}

void printPreorder(NodeT* iterator) {
    if(iterator) {
        printf("(%s, %d); ", iterator->name, iterator->age);
        printPreorder(iterator->left);
        printPreorder(iterator->right);
    }
}

void printHashTable(NodeT** BucketList, int nbOfCells) {
    for(int i = 0; i < nbOfCells; i++) {
        printf("%d-> ", i);
        printPreorder(BucketList[i]);
        printf("\n");
    }
}

int main()
{
    NodeT** BucketList = createHashTable(17);
//    if(BucketList) {
//        printf("succes");
//    }
    insert(BucketList, "Andrei Muresan", 20);
    insert(BucketList, "Ionut Oprisiu", 21);
    insert(BucketList, "Neghina Vlad", 22);
    insert(BucketList, "Craciunas Victor", 19);
    insert(BucketList, "Nastase Saipi", 24);
    insert(BucketList, "Vilau Paul", 18);
//    insert(BucketList, "Dragos Sandru", 18);
    printHashTable(BucketList, 17);
    return 0;
}
