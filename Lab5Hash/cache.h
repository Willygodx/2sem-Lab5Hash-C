#ifndef LAB5HASH_CACHE_H
#define LAB5HASH_CACHE_H

#include "functions.h"

unsigned int hashCalculate(const char *string);
void putInCache(struct hash* cache, const char* keyDomain, const char* valueIP);
void printCache(const struct hash* cache);
struct hash* createCache();

#endif //LAB5HASH_CACHE_H
