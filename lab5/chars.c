/* chars.c -- characters are small integers */
#include <stdio.h>

int main(void)
{
    printf("A: %d\n", '7' - '0');
    printf("B: %d\n", 'z' - 'a');
    printf("C: %d\n", 'a' - 'A');
    printf("D: %c\n", 'q' - 32);
    printf("E: %c\n", 65);
    printf("F: %d\n", 'A');
    printf("G: %d\n", 012);
    printf("H: %d\n", 0x23);
    printf("I: %c%c\n", '\101', '\x41');
    printf("J: %zu\n", sizeof "abc");
    printf("K: %s\n", "ab" "cd");

    return 0;
}
