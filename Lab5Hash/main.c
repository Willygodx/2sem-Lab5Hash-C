#include "functions.h"
#include "menu.h"
#include "memory.h"
#include "cache.h"
int main()
{
    struct hash* cache;
    cache = createCache();
    menu(*cache);
    freeCacheTable(cache);
    return 0;
}