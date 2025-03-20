#include <stdio.h>
#include <stdlib.h>

int OpenFile(FILE** file, char* filename);
int isWhiteSpace(char curChar);

void TokenizeString(FILE* file);
void HandleString(char* curChar, FILE* file);
void HandleChar(char* curChar, FILE* file);
void HandleStandardToken(char* curChar, FILE* file);
void HandleComment(char* curChar, FILE* file);

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
        switch(curChar)
        {
            // Handle string (denoted by ")
            case '\"':
                HandleString(&curChar, file);
                break;

            // Handle char (denoted by ')
            case '\'':
                HandleChar(&curChar, file);
                break;
            
            // Handle comment (denoted by /, the * is handled in the function)
            case '/':
                HandleComment(&curChar, file);
                break;

            // Else, standard token
            default:
                HandleStandardToken(&curChar, file);
                break;
        }
    }
}

void HandleChar(char* curChar, FILE* file)
{
    printf("Character: \'");

    // Burn the "
    *curChar = getc(file);

    // Print until matching " found
    while(*curChar != '\'' && *curChar != EOF)
    {
       printf("%c", *curChar);
       *curChar = getc(file);
    }

    // Burn the "
    *curChar = getc(file);
    printf("\'\n");

    // ignore whitespace
    while(isWhiteSpace(*curChar) && *curChar != EOF)
    {
        *curChar = getc(file);
    }
}

void HandleStandardToken(char* curChar, FILE* file)
{
    // Handle regular tokens      
    printf("Token: ");

    // print character by character of token
    while(!isWhiteSpace(*curChar) && *curChar != EOF)
    {
        printf("%c", *curChar);
        *curChar = getc(file);
    }

    // ignore whitespace
    while(isWhiteSpace(*curChar) && *curChar != EOF)
    {
        *curChar = getc(file);
    }

    printf("\n");
}

void HandleString(char* curChar, FILE* file)
{
    printf("String: \"");

    // Burn the "
    *curChar = getc(file);

    // Print until matching " found
    while(*curChar != '\"' && *curChar != EOF)
    {
       printf("%c", *curChar);
       *curChar = getc(file);
    }

    // Burn the "
    *curChar = getc(file);
    printf("\"\n");

    // ignore whitespace
    while(isWhiteSpace(*curChar) && *curChar != EOF)
    {
        *curChar = getc(file);
    }
}

void HandleComment(char* curChar, FILE* file)
{
    // Get next char
    *curChar = getc(file);

    // Handle it not being a comment
    if(*curChar != '*')
    {
        // Adjust file pointer back
        fseek(file, -2, SEEK_CUR);

        // Get the character as it is meant to be
        *curChar = getc(file);

        // Handle the rest of the string as normal
        HandleStandardToken(curChar, file);
        return;
    }

    // Comment flag
    int isReadingComment = 1;

    while(isReadingComment)
    {
        // Keep track of last character
        char lastChar = *curChar;

        // Print until matching / found
        while(*curChar != '/' && *curChar != EOF)
        {
            lastChar = *curChar;
            *curChar = getc(file);
        }

        // Check that it is closing the comment
        if(lastChar == '*' && *curChar == '/')
        {
            isReadingComment = 0;
        }
    }

    // Burn the "/""
    *curChar = getc(file);

    // ignore whitespace
    while(isWhiteSpace(*curChar) && *curChar != EOF)
    {
        *curChar = getc(file);
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
