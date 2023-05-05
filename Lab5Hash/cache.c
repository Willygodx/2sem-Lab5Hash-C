#include "cache.h"

unsigned int hashCalculate(const char* string) {
    int hash = 0;
    for (int i = 0; i < strlen(string); i++) {
        hash += string[i];
    }
    return hash % HASH_SIZE_MAX;
}

void putInCache(struct hash* cache, const char* keyDomain, const char* valueIP) {
    int temp = hashCalculate(keyDomain);
    while (cache->hash[temp] != NULL && temp < cache->size) {
        temp++;
    }
    if (temp >= cache->size) {
        struct hashNode* old = cache->hash[0];
        for(int i = 0; i < cache->size - 1; i++) {
            cache->hash[i] = cache->hash[i + 1];
        }
        free(old);
        cache->hash[temp - 1] = NULL;
        temp--;
    }
    struct hashNode* hash = malloc(sizeof(struct hashNode));
    hash->keyDomain = strdup(keyDomain);
    hash->valueIP = strdup(valueIP);
    hash->next = NULL;
    cache->hash[temp] = hash;
}

void printCache(const struct hash* cache)
{
    for (int i = cache->size - 1; i > 0; i--)
    {
        struct hashNode* hash = cache->hash[i];
        if (hash != NULL)
        {
            printf("%s - %s\n", hash->keyDomain, hash->valueIP);
        }
    }
    printf("\n");
}

struct hash* createCache() {
    struct hash *cache = (struct hash*) malloc(sizeof(struct hash));
    cache->size = HASH_SIZE_MAX;
    cache->hash = (struct hashNode**) calloc(HASH_SIZE_MAX, sizeof(struct hashNode*));
    for (int i = 0; i < HASH_SIZE_MAX; i++) {
        cache->hash[i] = NULL;
    }
    return cache;
}