#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Common declarations
#define MAX_TEXTFILE_SIZE 4096
#define MAX_FILENAME_LENGTH 80

size_t readText(FILE* file, char text[], size_t maxTextSize)
{
    int c;
    int count = 0;
    while ((c = fgetc(file)) != EOF && count < maxTextSize - 1) {
        text[count] = c;
        count++;
    }
    text[count] = '\0';
    return count;
}

size_t readCipherBook(FILE* file, char text[], size_t maxTextSize)
{
    size_t textLength = readText(file, text, maxTextSize);
    size_t count = 0;
    char* out = text;

    for (size_t i = 0; i < textLength; i++) {
        if (!isspace(text[i])) {
            out[count++] = text[i];
        }
    }
    out[count] = '\0';
    return count;
}

int main(void)
{
    char filename[MAX_FILENAME_LENGTH] = "";
    char text[MAX_TEXTFILE_SIZE] = "";
    FILE* file = NULL;
    size_t textLength = 0;

    scanf("%80s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found... program will fail with segmentation fault\n");
    }
    textLength = readCipherBook(file, text, MAX_TEXTFILE_SIZE);
    fclose(file);

    printf("%s\n", text);
    printf("Size of cipherfile is %zu\n", textLength);
    return 0;
}
