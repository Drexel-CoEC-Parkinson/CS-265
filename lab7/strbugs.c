/* strbugs.c -- shout two words.  One of them crashes. */
#include <stdio.h>
#include <ctype.h>

void shout(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = toupper(s[i]);
}

int main(void)
{
    char first[] = "hello";
    char *second = "world";

    shout(first);
    printf("%s\n", first);

    shout(second);
    printf("%s\n", second);

    return 0;
}
