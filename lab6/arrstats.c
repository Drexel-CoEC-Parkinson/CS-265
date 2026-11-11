/* arrstats.c -- statistics on an array of integers
 *
 * Name:
 *
 * main() is written for you. Don't change it.
 * Write the five functions at the bottom of the file.
 */
#include <stdio.h>

#define MAX 100

int find_max(int a[], int n);
double mean(int a[], int n);
int count_above(int a[], int n, double limit);
void reverse(int a[], int n);
void print_array(int a[], int n);

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

    double avg = mean(values, count);

    printf("Count: %d\n", count);
    printf("Max: %d\n", find_max(values, count));
    printf("Mean: %.2f\n", avg);
    printf("Above mean: %d\n", count_above(values, count, avg));

    reverse(values, count);
    printf("Reversed: ");
    print_array(values, count);

    return 0;
}

/* Return the largest of the n values in a. */
int find_max(int a[], int n)
{
    /* TODO */
    return 0;
}

/* Return the mean (average) of the n values in a. */
double mean(int a[], int n)
{
    /* TODO */
    return 0.0;
}

/* Return how many of the n values in a are strictly greater than limit. */
int count_above(int a[], int n, double limit)
{
    /* TODO */
    return 0;
}

/* Reverse the n values in a, in place: no second array. */
void reverse(int a[], int n)
{
    /* TODO */
}

/* Print the n values in a on one line, separated by single spaces,
 * then a newline.  No space after the last value. */
void print_array(int a[], int n)
{
    /* TODO */
    printf("\n");
}
