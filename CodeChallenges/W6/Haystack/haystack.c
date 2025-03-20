#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strstr(char* haystack, char* needle);

int main()
{
    // Testing vars
    char* haystack = "This is a test string.";
    char* needle = "test";

    // Find needle
    char* result = my_strstr(haystack, needle);

    // Print results
    if(result)
    {
        printf("Found needle at: %s\n", result);
    }

    else
    {
        printf("Needle not found\n");
    }
}

char* my_strstr(char* haystack, char* needle)
{
    // Iterate through each character
    for(int i = 0; haystack[i] != '\0'; i++)
    {
        // If first character is the first needle character, compare
        if(haystack[i] == needle[0])
        {
            // Return addr if needed
            if(strncmp(&(haystack[i]), needle, strlen(needle)) == 0)
            {
                return &(haystack[i]);
            }
        }
    }

    return NULL;
}