#ifndef LAB5HASH_FUNCTIONS_H
#define LAB5HASH_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE_MAX 10
#define STRING_SIZE_MAX 1024

struct hashNode {
    char* keyDomain;
    char* valueIP;
    struct hashNode* next;
};

struct cacheTable {
    int size;
    struct hashNode** table;
};

void addToFile(const char* fileName, char* keyDomain, char* valueIP);
void readFile(struct cacheTable* cache, char* fileName);
void noDomainInCache (int counter, char* fileName);
void findIpByDomain(struct cacheTable* cache, char* fileName);
void findDomainByIp(void);

#endif //LAB5HASH_FUNCTIONS_H
