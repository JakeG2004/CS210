#include <stdio.h>
#include <stdlib.h>

int OpenFile(FILE** file, char* filename);
int isWhiteSpace(char curChar);

void TokenizeString(FILE* file);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Error: Usage is ./a.out <infile>\n");
        exit(-1);
    }

    FILE* file = NULL;

    if(!OpenFile(&file, argv[1]))
    {
        printf("Failed to open file. Exiting...\n");
        exit(-1);
    }

    TokenizeString(file);
}

void TokenizeString(FILE* file)
{
    char curChar = getc(file);

    while(curChar != EOF)
    {
        printf("Token: ");
        
        while(!isWhiteSpace(curChar) && curChar != EOF)
        {
            printf("%c", curChar);
            curChar = getc(file);
        }

        while(isWhiteSpace(curChar) && curChar != EOF)
        {
            curChar = getc(file);
        }

        printf("\n");
    }
}

// 1 if file open success, 0 if not
int OpenFile(FILE** file, char* filename)
{
    *file = fopen(filename, "r");
    if(*file == NULL)
    {
        return 0;
    }

    return 1;
}

int isWhiteSpace(char curChar)
{
    char* whiteSpace = " \t\n";

    for(int i = 0; i < 3; i++)
    {
        if(curChar == whiteSpace[i])
        {
            return 1;
        }
    }

    return 0;
}