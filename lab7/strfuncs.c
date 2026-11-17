/* strfuncs.c -- four string functions
 *
 * Name:
 *
 * main() is written for you. Don't change it.
 * Write the four functions at the bottom of the file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_char(const char *s, char c);
void str_upper(char *s);
void str_reverse(char *s);
char *str_dup(const char *s);

int main(void)
{
    char line[100];

    while (fgets(line, 100, stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';      /* remove the newline */
        if (line[0] == '\0')
            break;

        char *copy = str_dup(line);
        if (copy == NULL) {
            printf("Out of memory\n");
            return 1;
        }

        printf("%s\n", line);
        printf("  o's: %d\n", count_char(line, 'o'));
        str_upper(copy);
        printf("  upper: %s\n", copy);
        str_reverse(line);
        printf("  reversed: %s\n", line);

        free(copy);
    }

    return 0;
}

/* Return how many times c appears in s. */
int count_char(const char *s, char c)
{
    /* TODO */
    return 0;
}

/* Change every lowercase letter in s to uppercase, in place. */
void str_upper(char *s)
{
    /* TODO */
}

/* Reverse s in place: "abc" becomes "cba". */
void str_reverse(char *s)
{
    /* TODO */
}

/* Return a new copy of s in memory from malloc, or NULL if malloc fails.
 * The caller frees it. */
char *str_dup(const char *s)
{
    /* TODO */
    return NULL;
}
