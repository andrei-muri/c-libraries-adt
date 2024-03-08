#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THRESHOLD 0.7

typedef struct node {
    char name[25];
    int age;
    struct node* left;
    struct node* right;
} NodeT;

typedef struct {
    double treshHold;
    int nbOfCells;
    int nbOfElements;
    NodeT** BucketList;
} HashTable;

HashTable* createHashTable(int nbOfCells);
NodeT* findMin(NodeT* iterator);
HashTable* reallocHashTable(HashTable* hashTable, int nbOfCells);
NodeT* createNode(const char* name, int age);
NodeT* findBST(NodeT* root, char* name);
int getAge(HashTable* hashTable, char* name);
void rehash(HashTable* hashTable, NodeT* root);
int hash(char* key, int nbOfCells);
NodeT* insertInBST(NodeT* root, char* key, int value);
NodeT* deleteInBST(NodeT* root, char* name);
HashTable* insert(HashTable* hashTable, char* key, int value);
void deleteNode(HashTable* hashTable, char* key);
void printPreorder(NodeT* iterator);
void printHashTable(HashTable* hashTable);


int main() {
    int nbOfNodes = 17;
    HashTable* NameAge = createHashTable(nbOfNodes);
//    if(BucketList) {
//        printf("success");
//    }
    NameAge = insert(NameAge, "Andrei Muresan", 20);
    NameAge = insert(NameAge, "Neghina Vlad", 22);
    NameAge = insert(NameAge, "Craciunas Victor", 19);
    NameAge = insert(NameAge, "Nastase Saipi", 24);
    NameAge = insert(NameAge, "Vilau Paul", 18);
    NameAge = insert(NameAge, "Neghina Paraschiva", 18);
    NameAge = insert(NameAge, "Neghina Cristina", 18);
//    printHashTable(NameAge);
//    int newNbOfNodes = 23;
//    NameAge = reallocHashTable(NameAge, newNbOfNodes);
    NameAge = insert(NameAge, "Fracea Raula", 40);
//    printf("\n\n\n");
//    printHashTable(NameAge);
//    deleteNode(NameAge, "Fracea Raula");
    NameAge = insert(NameAge, "Pop Alexandra", 18);
    NameAge = insert(NameAge, "Moga Diana", 18);
    NameAge = insert(NameAge, "Oprisor Mara", 18);
    NameAge = insert(NameAge, "Tofan George", 18);
    NameAge = insert(NameAge, "Seulean Dragos", 18);
    NameAge = insert(NameAge, "Tianu Cosmin", 18);
    NameAge = insert(NameAge, "Marta Dula", 18);
    NameAge = insert(NameAge, "Andreea Marin", 18);
    NameAge = insert(NameAge, "Andreea Marculescu", 18);
    NameAge = insert(NameAge, "Andreea Iustin", 18);
    NameAge = insert(NameAge, "Andreea Dragos", 18);
    NameAge = insert(NameAge, "Marin Miliardar", 18);
    printHashTable(NameAge);
    int age = getAge(NameAge, "Andrei Muresan");
    printf("%d\n", age);
    deleteNode(NameAge, "Marin Miliardar");
    printHashTable(NameAge);
    return 0;
}

HashTable* createHashTable(int nbOfCells) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if(hashTable) {
        hashTable->BucketList = (NodeT**)calloc(nbOfCells, sizeof(NodeT*));
        hashTable->treshHold = 0;
        hashTable->nbOfElements = 0;
        hashTable->nbOfCells = nbOfCells;
    }
    return hashTable;
}

NodeT* findMin(NodeT* iterator) {
    while(iterator->left) {
        iterator = iterator->left;
    }
    return iterator;
}


NodeT* deleteInBST(NodeT* root, char* name) {
    if(!root) {
        printf("Element %s not found!\n", name);
    } else if(strcmp(root->name, name) > 0) {
        root->left = deleteInBST(root->left, name);
    } else if(strcmp(root->name, name) < 0) {
        root->right = deleteInBST(root->right, name);
    } else {
        if(root->left && root->right) {
            NodeT* temp = findMin(root->right);
            if(temp != NULL) {
                strcpy(root->name, temp->name);
                root->age = temp->age;
                root->right = deleteInBST(root->right, temp->name);
            }
        } else {
            NodeT* temp = root;
            if(root->left) {
                root = root->left;
            } else if(root->right) {
                root = root->right;
            } else {
                root = NULL;
            }
            free(temp);
        }
    }
    return root;
}

void rehash(HashTable* hashTable, NodeT* root) {
    if(root) {
        hashTable = insert(hashTable, root->name, root->age);
        rehash(hashTable, root->left);
        rehash(hashTable, root->right);
    }
}

HashTable* reallocHashTable(HashTable* hashTable, int nbOfCells) {
    if(hashTable->BucketList) {
        HashTable* newHT = createHashTable(nbOfCells);
        for(int i = 0; i < hashTable->nbOfCells; i++) {
            rehash(newHT, hashTable->BucketList[i]);
        }
        hashTable = newHT;
    }
    return hashTable;
}

int hash(char* key, int nbOfCells) {
    int hashCode = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        hashCode = ((int)key[i] * i + hashCode) % 1061;
    }
    return hashCode % nbOfCells;
}


NodeT* createNode(const char* name, int age) {
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
//        printf("%s", key);
    } else {
//        printf("%s", root->name);
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

NodeT* findBST(NodeT* root, char* name) {
    if(!root) {
        printf("Not found!\n");
        return NULL;
    } else if(strcmp(root->name, name) > 0) {
        return findBST(root->left, name);
    } else if(strcmp(root->name, name) < 0) {
        return findBST(root->right, name);
    } else {
        return root;
    }
}

int getAge(HashTable* hashTable, char* name) {
    int index = hash(name, hashTable->nbOfCells);
    NodeT* node = NULL;
    if(hashTable->BucketList[index]) {
        node = findBST(hashTable->BucketList[index], name);
    }
    if(node) {
        return node->age;
    }
    return -1;
}

HashTable* insert(HashTable* hashTable, char* key, int value) {
    int index = hash(key, hashTable->nbOfCells);
    hashTable->BucketList[index] = insertInBST(hashTable->BucketList[index], key, value);
    hashTable->nbOfElements++;
    hashTable->treshHold = (double)hashTable->nbOfElements / (double)hashTable->nbOfCells;
    if(hashTable->treshHold > THRESHOLD) {
        hashTable = reallocHashTable(hashTable, hashTable->nbOfCells * 2);
    }
//    printf("%d\n", hashTable->nbOfCells);
    return hashTable;
}

void deleteNode(HashTable* hashTable, char* key) {
    int index = hash(key, hashTable->nbOfCells);
    hashTable->BucketList[index] = deleteInBST(hashTable->BucketList[index], key);
    hashTable->nbOfElements--;
    hashTable->treshHold = (float)hashTable->nbOfElements / (float)hashTable->nbOfCells;
}

void printPreorder(NodeT* iterator) {
    if(iterator) {
        printf("(%s, %d); ", iterator->name, iterator->age);
        printPreorder(iterator->left);
        printPreorder(iterator->right);
    }
}


void printHashTable(HashTable* hashTable) {
    for(int i = 0; i < hashTable->nbOfCells; i++) {
        printf("%d-> ", i);
        printPreorder(hashTable->BucketList[i]);
        printf("\n");
    }
}
