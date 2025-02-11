#include <stdio.h>
#include <stdlib.h>

void CompressInput(char* str, int n);

const int MAX_STR_SIZE = 100;

int main()
{
    printf("Enter string to be compressed: ");
    char* inString = (char*)malloc(sizeof(char) * MAX_STR_SIZE);
    fgets(inString, MAX_STR_SIZE - 1, stdin);
    inString[MAX_STR_SIZE - 1] = '\0';

    printf("\nCOMPRESSED INPUT: ");
    CompressInput(inString, MAX_STR_SIZE);

    free(inString);
}

void CompressInput(char* str, int n)
{
    char* compStr = (char*)malloc(sizeof(char) * n);
    int curStringIndex = 0;

    int totalDupes = 0;

    for(int i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        int charCount = 1;
        compStr[curStringIndex] = str[i];
        curStringIndex++;

        while(str[i] == str[i+1])
        {
            totalDupes++;
            charCount++;
            i++;

            if(i >= n)
            {
                break;
            }
        }

        compStr[curStringIndex] = (char)(charCount + '0');
        curStringIndex++;
    }

    if(totalDupes == 0)
    {
        printf("%s", str);
    }

    else
    {
        printf("%s\n", compStr);
    }

    free(compStr);
}