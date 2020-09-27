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

size_t readMessage(FILE* file, char text[], size_t maxTextSize)
{
    size_t textLength = readText(file, text, maxTextSize);
    char *out = text;
    int count = 0;

    for (size_t i = 0; i < maxTextSize-1 && i < textLength; i++) {
        if (text[i] == '\t') {
            out[i] = 96;
        } else if (text[i] == '\n') {
            out[i] = 97;
        } else {
            out[i] = (int)(text[i] - 31);
        } count++;
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
    textLength = readMessage(file, text, MAX_TEXTFILE_SIZE);
    fclose(file);

    for(size_t i=0; i < textLength; i++) {
        printf("%d ", text[i]);
    }
    printf("\nSize of message is %zu\n", textLength);
    return 0;
}
