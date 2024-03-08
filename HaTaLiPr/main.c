#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELETED (NodeT*)0x00000069

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

int hash(char* name, int nbOfCells) {
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
            if((*hashTable)->BucketList[i] && (*hashTable)->BucketList[i] != DELETED) {
                insert(&newHT, (*hashTable)->BucketList[i]->name, (*hashTable)->BucketList[i]->age);
            }
        }
    }
    return newHT;
}

void insert(HashTable** hashTable, char* name, int age) {
    int index = hash(name, (*hashTable)->nbOfCells);
    while(index < (*hashTable)->nbOfCells && (*hashTable)->BucketList[index] && (*hashTable)->BucketList[index] != DELETED) {
        index++;
    }
    if(index == (*hashTable)->nbOfCells) {
        printf("Hash Table overflow!\n");
        return;
    }
    (*hashTable)->BucketList[index] = createNode(name, age);
    (*hashTable)->nbOfElements++;
    (*hashTable)->treshold = (float)(*hashTable)->nbOfElements / (float)(*hashTable)->nbOfCells;
    if((*hashTable)->treshold > 0.5) {
        HashTable* temp = reallocHashTable(hashTable, (*hashTable)->nbOfCells * 2);
        if(temp) {
            free(*hashTable);
            *hashTable = temp;
        }
    }
}

void deleteElement(HashTable** hashTable, char* name) {
    int index = hash(name, (*hashTable)->nbOfCells);
    int initialHash = index;
    while(index < (*hashTable)->nbOfCells && (*hashTable)->BucketList[index] && strcmp((*hashTable)->BucketList[index]->name, name) != 0) {
        index++;
    }
    if(index == (*hashTable)->nbOfCells || !(*hashTable)->BucketList[index]) {
        printf("Pair with name %s not found!\n", name);
        return;
    }
    int deletedIndex = index++;
    int switchIndex = deletedIndex;
    while(index < (*hashTable)->nbOfCells && (*hashTable)->BucketList[index]) {
        if((*hashTable)->BucketList[index] != DELETED && hash((*hashTable)->BucketList[index]->name, (*hashTable)->nbOfCells) == initialHash) {
            switchIndex = index;
        }
        index++;
    }
    free((*hashTable)->BucketList[deletedIndex]);
    if(switchIndex == deletedIndex) {
        (*hashTable)->BucketList[deletedIndex] = NULL;
        (*hashTable)->BucketList[deletedIndex] = DELETED;
    } else {
        NodeT* temp = (*hashTable)->BucketList[switchIndex];
        free((*hashTable)->BucketList[switchIndex]);
        (*hashTable)->BucketList[switchIndex] = DELETED;
        (*hashTable)->BucketList[deletedIndex] = temp;
    }
    (*hashTable)->nbOfElements--;
    (*hashTable)->treshold = (float)(*hashTable)->nbOfElements / (float)(*hashTable)->nbOfCells;
    if((*hashTable)->treshold < 0.1) {
        HashTable* temp = reallocHashTable(hashTable, (*hashTable)->nbOfCells / 2);
        if(temp) {
            free(*hashTable);
            *hashTable = temp;
        }
    }
}

int getAge(HashTable* hashTable, char* name) {
    int index = hash(name, hashTable->nbOfCells);
    while(index < hashTable->nbOfCells && hashTable->BucketList[index] && strcmp(hashTable->BucketList[index]->name, name) != 0) {
        index++;
    }
    if(index == hashTable->nbOfCells || !hashTable->BucketList[index]) {
        printf("Pair with name %s not found!\n", name);
        return -1;
    }
    return hashTable->BucketList[index]->age;
}

void print(HashTable* hashTable, FILE* output) {
    for(int i = 0; i < hashTable->nbOfCells; i++) {
        fprintf(output, "%d-> ", i);
        if(hashTable->BucketList[i] && hashTable->BucketList[i] != DELETED)
            fprintf(output, "(%s, %d)", hashTable->BucketList[i]->name, hashTable->BucketList[i]->age);
        if(hashTable->BucketList[i] == DELETED) {
            fprintf(output, "DELETED");
        }
    fprintf(output, "\n");
    }
}

int main()
{
    HashTable* NameAge = newHashTable(17);
    insert(&NameAge, "Muresan Andrei", 20);
    insert(&NameAge, "Mustatea Raul", 21);
    insert(&NameAge, "Craciunas Victor", 22);
    insert(&NameAge, "Vonica Paul", 19);
    insert(&NameAge, "Nastase Andrei", 18);
    insert(&NameAge, "Raul Gonzalez", 18);
    insert(&NameAge, "Mishu costache", 18);
    insert(&NameAge, "Mircea Manolescu", 18);
    insert(&NameAge, "Iordache Sebastian", 18);
    deleteElement(&NameAge, "Mircea Manolescu");
    deleteElement(&NameAge, "Muresan Andrei");
    deleteElement(&NameAge, "Mustatea Raul");
    deleteElement(&NameAge, "Vonica Paul");
    deleteElement(&NameAge, "Craciunas Victor");
    deleteElement(&NameAge, "Nastase Andrei");
    deleteElement(&NameAge, "Raul Gonzalez");
    deleteElement(&NameAge, "Mishu costache");

    FILE* output = fopen("output.txt", "w");
    print(NameAge, output);
    fclose(output);
    return 0;
}
