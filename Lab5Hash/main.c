#include "functions.h"
#include "menu.h"
#include "memory.h"

int main()
{
    struct cacheTable cache = {HASH_SIZE_MAX, calloc(HASH_SIZE_MAX, sizeof(struct hashNode*)) };
    menu(cache);
    freeCacheTable(&cache);
    return 0;
}