/* minmax.c -- one function that returns two answers, and one that returns
 * a new array
 *
 * Name:
 *
 * main() is written for you. Don't change it.
 * Write the two functions at the bottom of the file.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void min_max(int a[], int n, int *min, int *max);
int *copy_array(int a[], int n);

int main(void)
{
    char line[100];
    int values[MAX];
    int x, count = 0;

    while (fgets(line, 100, stdin) != NULL) {
        if (line[0] == '\n')
            break;
        if (sscanf(line, "%d", &x) != 1) {
            printf("skipping: %s", line);
            continue;
        }
        if (count == MAX) {
            printf("Stopped at %d values\n", MAX);
            break;
        }
        values[count] = x;
        count++;
    }

    if (count == 0) {
        printf("No numbers\n");
        return 0;
    }

    int lo, hi;
    min_max(values, count, &lo, &hi);
    printf("Min: %d\n", lo);
    printf("Max: %d\n", hi);

    int *doubled = copy_array(values, count);
    if (doubled == NULL) {
        printf("Out of memory\n");
        return 1;
    }
    for (int i = 0; i < count; i++)
        doubled[i] *= 2;

    printf("Original:");
    for (int i = 0; i < count; i++)
        printf(" %d", values[i]);
    printf("\n");

    printf("Doubled:");
    for (int i = 0; i < count; i++)
        printf(" %d", doubled[i]);
    printf("\n");

    free(doubled);
    return 0;
}

/* Store the smallest of the n values in *min and the largest in *max. */
void min_max(int a[], int n, int *min, int *max)
{
    /* TODO */
}

/* Return a new array from malloc holding a copy of the n values in a,
 * or NULL if malloc fails.  The caller frees it. */
int *copy_array(int a[], int n)
{
    /* TODO */
    return NULL;
}
