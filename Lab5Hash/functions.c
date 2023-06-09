#include "check.h"
#include "cache.h"

void pushDnsToFile(const char* fileName, char* keyDomain, char* valueIP) {
    FILE* fileDNS = fopen(fileName, "a");
    if (fileDNS == NULL) {
        printf("Error: cannot open the file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fileDNS, "%s IN A %s\n", keyDomain, valueIP);
    fclose(fileDNS);
}

void readDnsFile(struct hash* cache, char* fileName) {
    char string[STRING_SIZE_MAX];
    char keyDomain[STRING_SIZE_MAX];
    char valueIP[256];
    checkRewriteIp(fileName);
    int counter = 0;
    FILE* fileDNS = fopen("dnsList.txt", "r");
    if (fileDNS == NULL) {
        printf("Error: cannot open the file!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(string, sizeof(string), fileDNS) != NULL)
    {
        if (sscanf(string, "%255s IN A %255s", keyDomain, valueIP) == 2 && strcmp(keyDomain, fileName) == 0 && checkIP(valueIP) == 1)
        {
            putInCache(cache, fileName, valueIP);
            counter++;
        }
    }
    noDomainInCache(counter, fileName);
    fclose(fileDNS);
}

void noDomainInCache(int counter, char* fileName)
{
    if(counter == 0)
    {
        int chooseButton = 0;
        printf("This domain is not found. Input: 1 - add new domain; 2 - try another one domain.\n>");
        checkValueOneTwo(&chooseButton);
        if(chooseButton == 1)
        {
            char* valueIp = malloc(16);
            do {
                printf("IP-address: \n>");
                fflush(stdin);
                fgets(valueIp, 16, stdin);
            } while (!checkIP(valueIp));
            pushDnsToFile("dnsList.txt", fileName, valueIp);
        }
        if(chooseButton == 2)
        {
            printf("Input domain:\n> ");
            scanf("%255s", fileName);
        }
    }
}

void findIpByDomain(struct hash* cache, char* fileName)
{
    struct hashNode* hash;
    int counter = 0;
    int i = hashCalculate(fileName);
    while (i >= 0 && i < cache->size)
    {
        hash = cache->hash[i];
        while (hash != NULL)
        {
            if(strcmp(hash->keyDomain, fileName) == 0) break;
            hash = hash->next;
        }
        if(hash != NULL)
        {
            if(counter == 0) printf("\n%s\n", hash->valueIP);
            counter++;
            for(int j = i; j < cache->size - 1; j++) cache->hash[j] = cache->hash[j + 1];
            cache->hash[cache->size - 1] = hash;
        }
        i++;
    }
    if(counter == 0)
    {
        readDnsFile(cache, fileName);
        findIpByDomain(cache, fileName);
    }
}

void findDomainByIp(void)
{
    char needIP[256];
    printf("IP-address: \n>");
    scanf("%255s", needIP);
    FILE* fileDNS = fopen("dnsList.txt", "r");
    if (fileDNS == NULL) {
        printf("Error: cannot open the file!\n");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    int counter = 0;
    char string[STRING_SIZE_MAX];
    char keyDomain[STRING_SIZE_MAX];
    char valueIP[256];
    while (fgets(string, sizeof(string), fileDNS) != NULL) {
        if (sscanf(string, "%255s IN A %255s", keyDomain, valueIP) == 2 && strcmp(needIP, valueIP) == 0 && counter == 0) {
            printf("%s\n", keyDomain);
            counter++;
            strcpy(needIP, keyDomain);
        }
        if (sscanf(string, "%255s IN CNAME %255s", keyDomain, valueIP) == 2 && strcmp(needIP, valueIP) == 0 && counter == 1)
        {
            printf("%s\n", keyDomain);
        }
    }
    fclose(fileDNS);
    printf("\n");
    if(counter == 0)
    {
        printf("Error!\n>");
        findDomainByIp();
    }
}
