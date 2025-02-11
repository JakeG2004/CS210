#include <stdio.h>
#include <stdlib.h>

int OpenFile(FILE** file, char* filename);
int isWhiteSpace(char curChar);

void TokenizeString(FILE* file);

int main(int argc, char* argv[])
{
    // Ensure proper # of args
    if(argc != 2)
    {
        printf("Error: Usage is ./a.out <infile>\n");
        exit(-1);
    }

    // Get an empty file
    FILE* file = NULL;

    // Open file
    if(!OpenFile(&file, argv[1]))
    {
        printf("Failed to open file. Exiting...\n");
        exit(-1);
    }

    // Break string into tokens
    TokenizeString(file);

    // Close the file
    fclose(file);
}

void TokenizeString(FILE* file)
{
    // Get first char
    char curChar = getc(file);

    // While not at end of file
    while(curChar != EOF)
    {
        // Handle string
        if(curChar == '\"')
        {
            printf("String: \"");

            // Burn the "
            curChar = getc(file);

            // Print until matching " found
            while(curChar != '\"' && curChar != EOF)
            {
               printf("%c", curChar);
               curChar = getc(file);
            }

            // Burn the "
            curChar = getc(file);
            printf("\"\n");
        
            // ignore whitespace
            while(isWhiteSpace(curChar) && curChar != EOF)
            {
                curChar = getc(file);
            }

            // Go to next token
            continue;

        }

        // Handle regular tokens      
        printf("Token: ");

        // print character by character of token
        while(!isWhiteSpace(curChar) && curChar != EOF)
        {
            printf("%c", curChar);
            curChar = getc(file);
        }

        // ignore whitespace
        while(isWhiteSpace(curChar) && curChar != EOF)
        {
            curChar = getc(file);
        }

        // token finiished
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

// Return 1 if current char is whitespace, 0 if not
int isWhiteSpace(char curChar)
{
    if(curChar == ' ' || curChar == '\t' || curChar == '\n' || curChar == '\0')
    {
        return 1;
    }

    return 0;
}
