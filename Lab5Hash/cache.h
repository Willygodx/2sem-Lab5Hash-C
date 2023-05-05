#ifndef LAB5HASH_CACHE_H
#define LAB5HASH_CACHE_H

#include "functions.h"

unsigned int hashCalculate(const char *string);
void putInCache(struct cacheTable* cache, const char* keyDomain, const char* valueIP);
void printCache(const struct cacheTable* cache);

#endif //LAB5HASH_CACHE_H
