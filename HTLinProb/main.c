#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[30];
    int age;
} NodeT;

typedef struct {
    int nbOfCells;
    int nbOfElements;
    float treshold;
    NodeT** BucketList;
} HashTable;

NodeT* createNode(char* name, int age) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if(node) {
        strcpy(node->name, name);
        node->age = age;
    }
    return node;
}

HashTable* newHashTable(int nbOfCells) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if(hashTable) {
        hashTable->nbOfCells = nbOfCells;
        hashTable->nbOfElements = 0;
        hashTable->treshold = 0;
        hashTable->BucketList = (NodeT**)calloc(nbOfCells, sizeof(NodeT*));
    }
    return hashTable;
}

int hash(const char* name, int nbOfCells) {
    int hashCode = 0;
    for(int i = 0; name[i] != '\0'; i++) {
        hashCode = (name[i] * i + hashCode) % 1061;
    }
    return hashCode % nbOfCells;
}

void insert(HashTable** hashTable, char* name, int age);

HashTable* reallocHashTable(HashTable** hashTable, int nbOfCells) {
    HashTable* newHT = newHashTable(nbOfCells);
    if(newHT) {
        for(int i = 0; i < (*hashTable)->nbOfCells; i++) {
            if((*hashTable)->BucketList[i]) {
                insert(&newHT, (*hashTable)->BucketList[i]->name, (*hashTable)->BucketList[i]->age);
            }
        }
    }
    return newHT;
}

void insert(HashTable** hashTable, char* name, int age) {
    int index = hash(name, (*hashTable)->nbOfCells);
    while(index < (*hashTable)->nbOfCells && (*hashTable)->BucketList[index]) {
        index++;
    }
    if(index == (*hashTable)->nbOfCells) {
        printf("Hash Table overflow!\n");
        return;
    }
    (*hashTable)->BucketList[index] = createNode(name, age);
    (*hashTable)->nbOfElements++;
    (*hashTable)->treshold = (float)(*hashTable)->nbOfElements / (float)(*hashTable)->nbOfCells;
    if((*hashTable)->treshold > 0.6) {
        HashTable* temp = reallocHashTable(hashTable, (*hashTable)->nbOfCells * 2);
        if(temp) {
            (*hashTable) = temp;
        }
    }
}

void print(HashTable* hashTable) {
    for(int i = 0; i < hashTable->nbOfCells; i++) {
        printf("%d-> ", i);
        if(hashTable->BucketList[i])
            printf("(%s, %d)", hashTable->BucketList[i]->name, hashTable->BucketList[i]->age);
        printf("\n");
    }
}

int main() {
    HashTable* NameAge = newHashTable(17);
    insert(&NameAge, "Muresan Andrei", 20);
    insert(&NameAge, "Mustatea Raul", 21);
    insert(&NameAge, "Craciunas Victor", 22);
    insert(&NameAge, "Vonica Paul", 19);
    insert(&NameAge, "Nastase Andrei", 18);
    insert(&NameAge, "Nastase Andrei1", 18);
    insert(&NameAge, "Nastase Andrei2", 18);
    insert(&NameAge, "Nastase Andrei3", 18);
    insert(&NameAge, "Nastase Andrei4", 18);
    insert(&NameAge, "Nastase Andrei5", 18);
    insert(&NameAge, "Nastase Andrei6", 18);
    insert(&NameAge, "Nastase Andrei7", 18);
    print(NameAge);
    return 0;
}
