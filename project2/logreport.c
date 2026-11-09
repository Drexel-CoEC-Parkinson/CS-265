/*
 * logreport.c -- CS-265 Project 2
 *
 * Name:      TODO your name
 * Drexel ID: TODO your userid (e.g. abc123)
 * Date:      TODO
 *
 * Purpose:   Reads a web-server access log and prints a summary report.
 *
 * BONUS:     not attempted        <-- change to "attempted" if you do the
 *                                     malloc bonus (see project2.md)
 *
 * Build:     gcc -Wall -Wextra -g -std=c99 -o logreport logreport.c
 * Usage:     ./logreport [FILE]       (reads standard input if no FILE)
 */

#include <stdio.h>
#include <string.h>

#define LINE_LEN   512   /* longest input line, including '\n' and '\0' */
#define PATH_LEN   256   /* longest path, including '\0'                 */
#define MAX_PATHS  100   /* distinct paths you must be able to track     */
#define TOP_N      5     /* how many paths the report lists              */

/*
 * Suggested helper. Parse one log line. On success, fill in path,
 * *status, *bytes and *hour and return 1. If the line is malformed
 * (see the rules in project2.md), return 0.
 *
 * You may change this prototype, or add more functions -- this is a
 * starting point, not a requirement.
 */
int parse_line(const char line[], char path[], int *status, long *bytes,
               int *hour);

int main(int argc, char *argv[])
{
    FILE *in = stdin;
    char line[LINE_LEN];
    int lines_read = 0;

    /*
     * TODO (Part 1): command-line handling.
     *   - more than one argument   -> usage message on stderr, return 2
     *   - one argument             -> fopen it; on failure print
     *                                 "logreport: cannot open FILE" on
     *                                 stderr and return 1
     *   - no argument              -> keep reading from stdin
     * Remove the two (void) lines below once you use argc and argv.
     */
    (void) argc;
    (void) argv;

    while (fgets(line, LINE_LEN, in) != NULL) {
        lines_read++;

        /* TODO (Part 2): parse the line; count it as valid or malformed. */
        /* TODO (Parts 3-5): update your totals, status classes, hours,  */
        /*                   and path table.                             */
    }

    /* TODO: close the file if you opened one. */

    /* TODO (Part 6): print the full report in the exact format. */
    printf("Lines read:      %d\n", lines_read);

    return 0;
}

int parse_line(const char line[], char path[], int *status, long *bytes,
               int *hour)
{
    /* TODO (Part 2) -- replace this stub. */
    (void) line;
    (void) path;
    (void) status;
    (void) bytes;
    (void) hour;
    return 0;
}
