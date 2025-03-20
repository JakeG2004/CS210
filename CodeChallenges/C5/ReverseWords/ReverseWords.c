#include <stdio.h>
#include <stdlib.h>

const int MAX_STR_SIZE = 64;

void ReverseWords(char* str);

int main(int argc, char* argv[])
{
    ReverseWords(argv[1]);
}

void ReverseWords(char* str)
{
    // Get word count and construct 2d array
    // minimum of 1 word
    int wordCount = 1;

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ' ' || str[i] == '\t')
        {
            wordCount++;
        }
    }

    // Construct 2d array
    char** words = (char**)malloc(sizeof(char*) * wordCount);

    // Init 2d array
    for(int i = 0; i < wordCount; i++)
    {
        words[i] = (char*)malloc(sizeof(char) * MAX_STR_SIZE);
    }

    // Init all strings to \0
    for(int i = 0; i < wordCount; i++)
    {
        for(int j = 0; j < MAX_STR_SIZE; j++)
        {
            words[i][j] = '\0';
        }
    }

    // Get each word from the string
    int curIndex = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ' ' || str[i] == '\t')
        {
            curIndex++;
            continue;
        }

        sprintf(words[curIndex], "%s%c", words[curIndex], str[i]);
    }

    // Print results
    printf("\n===== REVERSED WORDS =====\n");
    for(int i = wordCount - 1; i >= 0; i--)
    {
        printf("%s ", words[i]);
    }

    printf("\n");

    // Free array
    for(int i = 0; i < wordCount; i++)
    {
        free(words[i]);
    }
    free(words);
}