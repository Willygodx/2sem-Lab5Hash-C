#include "check.h"

void freeHash(struct hashNode* node) {
    if (node != NULL) {
        free(node->keyDomain);
        free(node->valueIP);
        free(node);
    }
}

void freeCacheTable(struct hash* cache) {
    if (cache != NULL) {
        for (int i = 0; i < cache->size; i++) {
            struct hashNode *hash = cache->hash[i];
            while (hash != NULL) {
                struct hashNode *next = hash->next;
                freeHash(hash);
                hash = next;
            }
        }
        free(cache->hash);
        free(cache);
    }
}