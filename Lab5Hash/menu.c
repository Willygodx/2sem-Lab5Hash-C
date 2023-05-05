#include "check.h"
#include "cache.h"

void menu(struct hash cache)
{
    char fileName[STRING_SIZE_MAX];
    int chooseButton = 0;
    while(1)
    {
        printf("1.Find IP by domain.\n"
               "2.Find domain/domains by IP.\n"
               "3.Print cache hash.\n"
               "4.Exit\n>");
        fflush(stdin);
        checkValueForMenu(&chooseButton);
        rewind(stdin);
        switch (chooseButton)
        {
            case 1:
                printf("Enter domain: ");
                scanf("%255s", fileName);
                findIpByDomain(&cache, fileName);
                printf("\n");
                break;
            case 2:
                findDomainByIp();
                break;
            case 3:
                printCache(&cache);
                break;
            case 4:
                exit(EXIT_SUCCESS);
            default:
                printf("aahahahahahah");
                return;
        }
    }
}