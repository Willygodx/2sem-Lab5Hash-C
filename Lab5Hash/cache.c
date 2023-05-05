#include "cache.h"

unsigned int hashCalculate(const char* string) {
    int hash = 0;
    for (int i = 0; i < strlen(string); i++) {
        hash += string[i];
    }
    return hash % HASH_SIZE_MAX;
}

void putInCache(struct cacheTable* cache, const char* keyDomain, const char* valueIP) {
    int temp = hashCalculate(keyDomain);
    while (cache->table[temp] != NULL && temp < cache->size) {
        temp++;
    }
    if (temp >= cache->size) {
        struct hashNode* old = cache->table[0];
        for(int i = 0; i < cache->size - 1; i++) {
            cache->table[i] = cache->table[i + 1];
        }
        free(old);
        cache->table[temp - 1] = NULL;
        temp--;
    }
    struct hashNode* hash = malloc(sizeof(struct hashNode));
    hash->keyDomain = strdup(keyDomain);
    hash->valueIP = strdup(valueIP);
    hash->next = NULL;
    cache->table[temp] = hash;
}

void printCache(const struct cacheTable* cache)
{
    for (int i = cache->size - 1; i > 0; i--)
    {
        struct hashNode* hash = cache->table[i];
        if (hash != NULL)
        {
            printf("%s - %s\n", hash->keyDomain, hash->valueIP);
        }
    }
    printf("\n");
}