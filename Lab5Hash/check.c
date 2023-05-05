#include "check.h"

void checkValueOneTwo(int* value)
{
    while (scanf("%d", value) == 0 || *value < 1 || *value > 2 || getchar() != '\n')
    {
        printf("Error: wrong input.\n>");
        rewind(stdin);
    }
}

void checkValueForMenu(int* value)
{
    while (scanf("%d", value) == 0 || *value <= 0 || *value > 4 || getchar() != '\n')
    {
        printf("Error: wrong input.\n>");
        rewind(stdin);
    }
}

int checkIP(const char* valueIP) {
    if (valueIP == NULL) {
        return 0;
    }
    int number[4];
    int dotCounter = sscanf(valueIP, "%d.%d.%d.%d", &number[0], &number[1], &number[2], &number[3]);
    if (dotCounter != 4)
    {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (number[i] < 0 || number[i] > 255) {
            return 0;
        }
    }
    return 1;
}

void checkRewriteIp(char* fileName)
{
    int counter = 0;
    FILE* fileDNS = fopen("dnsList.txt", "r");
    if (fileDNS == NULL) {
        printf("Error: cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    char string[STRING_SIZE_MAX];
    char keyDomain[STRING_SIZE_MAX];
    char cname[STRING_SIZE_MAX + 1];
    while (fgets(string, sizeof(string), fileDNS) != NULL)
    {
        if (sscanf(string, "%255s IN CNAМЕ %255s", keyDomain, cname) == 2 && strcmp(keyDomain, fileName) == 0)
        {
            strcpy(fileName, cname);
            counter++;
            printf("%d", counter);
        }
    }
    fclose(fileDNS);
}