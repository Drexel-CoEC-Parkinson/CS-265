#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char word[100];
    char *copy;

    printf("Enter a word: ");
    if (scanf("%99s", word) != 1)
        return 1;

    copy = malloc(strlen(word) + 1);    /* +1 for the '\0' */
    if (copy == NULL)
        return 1;
    strcpy(copy, word);

    printf("copy of length %zu: %s\n", strlen(copy), copy);
    free(copy);
    return 0;
}
