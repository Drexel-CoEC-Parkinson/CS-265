/* strs.c -- arrays of char, pointers to char, and string.h */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char word[10] = "cat";
    char *lit = "dog";

    printf("A: %zu\n", sizeof word);
    printf("B: %zu\n", strlen(word));
    printf("C: %zu\n", sizeof lit);
    printf("D: %zu\n", strlen(lit));

    word[1] = 'u';
    printf("E: %s\n", word);

    word[1] = '\0';
    printf("F: %s\n", word);
    printf("G: %zu\n", strlen(word));

    strcpy(word, "kitten");
    printf("H: %s\n", word);

    printf("I: %d\n", strcmp("apple", "banana") < 0);
    printf("J: %d\n", strcmp(word, "kitten") == 0);

    return 0;
}
