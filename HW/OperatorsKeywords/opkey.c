#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ReadFileIntoString(const char* filename);
int isWhiteSpace(char curChar);
void TokenizeString(char* content);
void HandleString(char* content, int* index);
void HandleChar(char* content, int* index);
void HandleStandardToken(char* content, int* index);
void HandleComment(char* content, int* index);
int IsKeyword(char* content, int* index, char** keyword);
int IsOperator(char* content, int* index, char** operator);
void PrintTabs();

// Global counter for tabs
int tabs = 0;

int main(int argc, char* argv[])
{
    // Ensure correct usage
    if (argc != 2)
    {
        printf("Error: Usage is ./a.out <infile>\n");
        return -1;
    }

    // Open file, error if failed to get file
    char* content = ReadFileIntoString(argv[1]);
    if (!content)
    {
        printf("Failed to open file. Exiting...\n");
        return -1;
    }

    TokenizeString(content);
    free(content);
    return 0;
}

char* ReadFileIntoString(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);
    
    char* buffer = (char*)malloc(length + 1);
    if (!buffer)
    {
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

void TokenizeString(char* content)
{
    int index = 0;
    while (content[index] != '\0')
    {
        switch (content[index])
        {
            case '"':
                PrintTabs();
                HandleString(content, &index);
                break;
            case '\'':
                PrintTabs();
                HandleChar(content, &index);
                break;
            case '/':
                HandleComment(content, &index);
                break;
            default:
                PrintTabs();
                HandleStandardToken(content, &index);
                break;
        }
    }
}

void PrintTabs()
{
    for(int i = 0; i < tabs; i++)
    {
        printf("  ");
    }
}

void HandleChar(char* content, int* index)
{
    printf("Character: \'");
    (*index)++;

    while (content[*index] != '\'' && content[*index] != '\0')
    {
       printf("%c", content[*index]);
       (*index)++;
    }

    (*index)++;
    printf("'\n");

    while (isWhiteSpace(content[*index]) && content[*index] != '\0')
    {
        (*index)++;
    }
}

void HandleStandardToken(char* content, int* index)
{
    char* keyword = (char*)malloc(sizeof(char) * 64);

    if(IsKeyword(content, index, &keyword))
    {
        printf("Keyword: %s", keyword);
    }

    else if(IsOperator(content, index, &keyword))
    {
        printf("Operator: %s", keyword);
    }

    else
    {
        printf("Token: ");
        while (!isWhiteSpace(content[*index]) && content[*index] != '\0')
        {
            if(IsOperator(content, index, &keyword))
            {
                printf("\n");
                (*index)--;
                return;
            }

            printf("%c", content[*index]);
            (*index)++;
        }
    }

    printf("\n");

    while (isWhiteSpace(content[*index]) && content[*index] != '\0')
    {
        (*index)++;
    }
}

void HandleString(char* content, int* index)
{
    printf("String: \"");
    (*index)++;

    while (content[*index] != '"' && content[*index] != '\0')
    {
       printf("%c", content[*index]);
       (*index)++;
    }

    (*index)++;
    printf("\"\n");

    while (isWhiteSpace(content[*index]) && content[*index] != '\0')
    {
        (*index)++;
    }
}

void HandleComment(char* content, int* index)
{
    (*index)++;
    if (content[*index] != '*')
    {
        (*index)--;
        HandleStandardToken(content, index);
        return;
    }
    while (content[*index] != '\0')
    {
        char lastChar = content[*index];
        (*index)++;
        if (lastChar == '*' && content[*index] == '/')
        {
            (*index)++;
            break;
        }
    }

    while (isWhiteSpace(content[*index]) && content[*index] != '\0')
    {
        (*index)++;
    }
}

int isWhiteSpace(char curChar)
{
    return curChar == ' ' || curChar == '\t' || curChar == '\n';
}

int IsKeyword(char* content, int* index, char** keyword)
{
    char* keywords[] = {
        "character", "subtype", "natural", "integer", "mutator", "positive", 
        "constant", "others", "accessor", "boolean", "elsif", "float", "while", 
        "array", "class", "range", "ptr", "else", "exit", "func", "ifc", "null", "then", 
        "type", "when", "bool", "case", "and", "end", "out", "pkg", "proc","if", "in", "is", "of", "or"
    };

    for(int i = 0; i < (sizeof(keywords) / sizeof(char*)); i++)
    {
        if(strncmp(&(content[*index]), keywords[i], strlen(keywords[i])) == 0)
        {
            // If the word continues after the keyword, then it is not a keyword
            if(!isWhiteSpace(content[*index + strlen(keywords[i])]))
            {
                return 0;
            }

            *keyword = keywords[i];
            (*index) += strlen(keywords[i]);
            return 1;
        }
    }

    return 0;
}

int IsOperator(char* content, int* index, char** operator)
{
    char* doubleCharOps[] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "==", "!=", "=>", "{:", "}:"};
    char* singleCharOps = "<>()+-*/|&;,:=$@.[]{}";

    for(int i = 0 ; i < (sizeof(doubleCharOps) / sizeof(char*)); i++)
    {
        if(strncmp(&(content[*index]), doubleCharOps[i], strlen(doubleCharOps[i])) == 0)
        {
            *index += strlen(doubleCharOps[i]);
            *operator = doubleCharOps[i];
            return 1;
        }
    }

    for(int i = 0; i < singleCharOps[i] != '\0'; i++)
    {
        if(content[*index] == singleCharOps[i])
        {
            if(singleCharOps[i] == '{')
            {
                tabs++;
            }

            if(singleCharOps[i] == '}')
            {
                tabs--;
            }

            (*index)++;
            (*operator)[0] = singleCharOps[i];
            (*operator)[1] = '\0';
            return 1;
        }
    }

    return 0;
}
