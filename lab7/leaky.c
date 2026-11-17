/* leaky.c -- builds greetings on the heap and never gives the memory back */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_greeting(const char *name)
{
    char *g = malloc(strlen(name) + 8);

    strcpy(g, "Hello, ");
    strcat(g, name);
    return g;
}

int main(void)
{
    const char *names[3] = {"Ada", "Linus", "Grace"};

    for (int i = 0; i < 3; i++) {
        char *msg = make_greeting(names[i]);
        printf("%s\n", msg);
    }

    return 0;
}
