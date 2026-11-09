# CS-265: Advanced Programming Tools & Techniques
## Project 2: `logreport`, a Log Summary Tool in C

**Due:** Wednesday, December 9, 2026, 11:59 PM (submitted on Canvas)
**Points:** 100 (15% of course grade), plus up to 10 bonus points
**Late policy:** −10% / −20% / −30% per day late; not accepted after 4 days without prior discussions with me.

---

### The Scenario

You maintain the website for a student robotics club. The web server
adds one line to an *access log* for every request it handles. Each
line records who asked, what they asked for, when, how it went, and
how many bytes went back.

In Lab 3 you used `grep` and AWK to pull answers out of text files.
In this project you'll build a tool like that yourself, in C: a
program that reads a log and prints a summary report.

```
$ ./logreport tests/small.log
Log report
==========
Lines read:      15
...
```

### What You'll Practice

- Reading input line by line with `fgets`, and parsing it with `sscanf`
- Checking whether input is valid, and **reporting bad input without crashing**
- Arrays, including an array of strings and a pair of parallel arrays
- `argc`/`argv`, `fopen`/`fclose`, and reading from standard input
- Sending errors to `stderr`, and exiting with a meaningful exit status
- Printing output in an exact format, the way a tool feeding other tools must
- **Bonus:** dynamic memory with `malloc`/`realloc`/`free`, checked with `valgrind`

---

### Getting Started

Copy the whole project directory out of the materials repo **once**:

```bash
cd ~/CS265/materials && git pull
mkdir -p ~/CS265/project2
cp -r ~/CS265/materials/project2/* ~/CS265/project2/
cd ~/CS265/project2
gcc -Wall -Wextra -g -std=c99 -o logreport logreport.c
./logreport < tests/small.log
```

You now have the starter `logreport.c`, the self-check script
`check_p2.bash`, and the test logs in `tests/`. **Don't edit anything
in `tests/`.** The self-check script compares against those files.

The starter compiles cleanly, but all it does is count lines. It also
ignores its command-line arguments and always reads standard input,
which is why the command above uses `<`. If you run
`./logreport tests/small.log` before you finish Part 1, the program
will sit there waiting for you to type. Press **Ctrl-D** to end the
input, or **Ctrl-C** to quit.

**Don't run the `cp -r` again after you start working.** It would
copy the starter over your `logreport.c`. (The course `cp -i` alias
asks first. Answer `n`.) If we post a fix to the tests, the
announcement will tell you which files to copy again.

Use the course compile line every time:
`gcc -Wall -Wextra -g -std=c99`. Fix every warning. Warnings cost
points.

---

### The Log Format

Each line of a log looks like this:

```
2026-11-02 09:14:03 10.0.4.17 GET /index.html 200 5120
```

| # | Field  | Example       | Meaning                                    |
|---|--------|---------------|--------------------------------------------|
| 1 | date   | `2026-11-02`  | `YYYY-MM-DD`                               |
| 2 | time   | `09:14:03`    | `HH:MM:SS`, 24-hour clock                  |
| 3 | client | `10.0.4.17`   | who made the request (not checked)         |
| 4 | method | `GET`         | `GET`, `POST`, ... (not checked)           |
| 5 | path   | `/index.html` | what was requested, at most 255 characters |
| 6 | status | `200`         | HTTP status code                           |
| 7 | bytes  | `5120`        | size of the response in bytes              |

- Fields are separated by one or more spaces or tabs, and leading spaces are allowed.
- Anything after the seventh field is ignored.
- No line is longer than 510 characters.
- The last line of a file might not end with a newline. It still counts as a line.

#### When is a line malformed?

A line is **valid** only if **all** of these are true:

1. Your `sscanf` call that reads the seven fields returns **7**. In
   other words, there are at least 7 fields, and `%d` and `%ld` can
   read numbers at the start of fields 6 and 7.
2. The date has the form `Y-M-D` with integer parts, the month is 1–12, and the day is 1–31.
3. The time has the form `H:M:S` with integer parts, the hour is 0–23, and the minute and second are 0–59.
4. The status is between 100 and 599.
5. The byte count is 0 or more.

Every other line is **malformed**, including blank lines, comment lines,
and lines with a `-` where the byte count belongs. For each malformed
line, print this to **stderr** (*N* is the line number, counting from 1):

```
logreport: line N: malformed entry
```

and keep going. A malformed line counts toward "Lines read" and
"Malformed lines", and nothing else.

`tests/malformed.log` has examples of nearly every kind of bad line.
Read it.

---

### Command Line

| You run                        | Program must                                                     | Exit status |
|--------------------------------|------------------------------------------------------------------|-------------|
| `./logreport FILE`             | read `FILE`, print the report                                    | 0           |
| `./logreport`                  | read **standard input**, print the report                        | 0           |
| `./logreport FILE` (can't open)| print `logreport: cannot open FILE` on stderr, nothing on stdout | 1           |
| `./logreport A B` (2+ args)    | print `usage: logreport [FILE]` on stderr, nothing on stdout     | 2           |

Reading from standard input means all of these work:

```bash
./logreport < tests/week.log
grep ' 404 ' tests/week.log | ./logreport
```

Malformed lines don't change the exit status. A log full of garbage
still exits 0.

---

### The Report (exact; this is autograded)

Your output must match **exactly**: the same spacing, the same
capitalization, the same blank lines, and nothing extra. For
`tests/small.log`:

```
Log report
==========
Lines read:      15
Valid entries:   13
Malformed lines: 2
Total bytes:     290695
Average bytes:   22361.2
Distinct paths:  6

Status classes
  1xx: 0
  2xx: 9
  3xx: 2
  4xx: 1
  5xx: 1

Requests by hour
  09: 4
  10: 3
  13: 4
  14: 2
Busiest hour: 09 (4 requests)

Top 5 paths
      4  /index.html
      3  /events.html
      2  /css/style.css
      2  /signup
      1  /favicon.ico
```

The rules behind each section:

**Summary.** "Total bytes" is the sum of field 7 over the valid
entries. "Average bytes" is total bytes divided by valid entries,
printed with `%.1f`. If there are no valid entries, print `0.0`.
"Distinct paths" is how many different paths appeared in valid
entries.

> **Use `long` for byte totals, and print them with `%ld`.**
> `tests/week.log` adds up to more than 2,147,483,647 bytes, the
> largest value an `int` can hold on tux. An `int` total silently
> wraps around to a wrong, possibly negative, number. For the
> average, convert to `double` before dividing.

**Status classes.** A status's class is its first digit, so 404 goes
in `4xx`. Always print all five lines, even the zeros.

**Requests by hour.** Print one line for each hour that has at least
one valid entry, in order from 00 to 23, with two-digit hours (`%02d`).
Skip hours that have no entries. Hours are combined across all the
dates in the log. Then print the busiest hour. **If two or more hours
tie, the earliest hour wins.** In `small.log`, 09 and 13 both have 4,
so the report says 09.

The busiest-hour line always uses the word `requests`, even for a
count of 1: `Busiest hour: 17 (1 requests)`. Don't change it to
"request". The output is compared character by character.

If there are no valid entries, the section is just:

```
Requests by hour
Busiest hour: none
```

**Top 5 paths.** List the 5 paths with the most requests, most first.
Print each one with `printf("  %5d  %s\n", ...)`. **Break ties
alphabetically, in `strcmp` order.** That's why `/favicon.ico` beats
`/img/robot.jpg` for 5th place in `small.log`. In `strcmp` order,
uppercase comes before lowercase, so `/About.html` sorts before
`/about.html`. If there are fewer than 5 distinct paths, list them
all, but keep the heading `Top 5 paths`. If there are none, print
`  (none)`.

#### The path table

You need to remember each distinct path and how many times it
appeared. The starter defines `MAX_PATHS` (100) and `PATH_LEN` (256).
A simple design uses two **parallel arrays**:

```c
char paths[MAX_PATHS][PATH_LEN];   /* paths[i] is a string          */
int  counts[MAX_PATHS];            /* counts[i] goes with paths[i]  */
int  npaths = 0;                   /* how many slots are in use     */
```

`paths` is an array of 100 strings. Each string is a `char` array of
256, so `paths[i]` can go anywhere a string can: `strcmp`, `strcpy`,
or `printf("%s")`.

For each valid entry, search `paths[0..npaths-1]` with `strcmp`. If
you find the path, add 1 to its count. If you don't, `strcpy` the
path into slot `npaths`, set its count to 1, and increase `npaths`.
If the table is full, skip the new path, but **never write past the
end of the arrays.** (It's the same rule as Lab 5's `rev-array`.)
None of the graded base tests has more than 100 distinct paths.

To find the top 5, sort both arrays together. A selection sort is
fine at this size. Whenever you swap two counts, swap the two paths
as well. If you know how to use a `struct`, you may use one instead
of parallel arrays.

---

### Suggested Plan

Build the program in stages, and run it after each one. The
self-check compares whole reports, so expect most of it to fail until
Part 6. Until then, check your progress against the expected `.out`
files by eye.

1. **Command line.** Handle 0, 1, and 2+ arguments, including a file
   that can't be opened. Test it with `./logreport nope.log; echo $?`.
2. **Parsing.** Write `parse_line`. Print the malformed messages and
   get the counts right on `malformed.log` (19 lines, 14 malformed).
3. **Summary and status classes.** Totals, the average, and the five
   class counters. An `int` array of 5 works well for the counters.
4. **Hours.** Use an array of 24 counters, then find the busiest hour.
5. **Paths.** Build the table, sort it, and print the top 5.
6. **Exact format.** Put everything in the final layout, then run the
   self-check.

---

### C Toolbox

**`sscanf` returns how many fields it filled in.** That return value
is how you detect bad lines. **Always check it.**

```c
char word[32];
int n;
if (sscanf("count 42", "%31s %d", word, &n) == 2) {
    /* both fields were read */
}
```

- `%31s` reads one whitespace-separated word, **at most 31 characters**,
  into a 32-byte array. Always give `%s` a width that is one less than
  the array size. Without one, a long word overflows your array.
- `%d` reads an `int`. `%ld` reads a `long`, and its argument must be a `long *`.
- You can `sscanf` a string you already pulled out. For example, use
  `sscanf(date, "%d-%d-%d", ...)` on the date field. The `-` and `:` in
  the format have to match those characters exactly.

**Returning several values from one function.** A C function returns
only one value. `parse_line` needs to hand back four: the path, the
status, the bytes, and the hour. It does this the same way `sscanf`
does, by taking the **addresses** of the caller's variables:

```c
int parse_line(const char line[], char path[], int *status, long *bytes,
               int *hour);

/* in main: */
char path[PATH_LEN];
int status, hour;
long bytes;
if (parse_line(line, path, &status, &bytes, &hour)) {
    /* status, bytes, hour, and path now hold this line's values */
}
```

Inside `parse_line`, `status` is already an address. Pass it to
`sscanf` as `status`, without an `&`. Read or set the value through
it as `*status`, as in `if (*status < 100) ...`. An array parameter
like `path` already works this way with no `&` needed. We'll cover
the details in the pointers unit. If you'd rather avoid pointers for
now, you may do all the parsing inside `main` instead.

**Strings** (`#include <string.h>`): `strcmp(a, b)` returns 0 when the
strings are equal, a negative number when `a` sorts first, and a
positive number when `b` sorts first. `strcpy(dst, src)` copies `src`
into `dst`, which must be big enough to hold it.

**Files** (see `copy.c` in `example_code/branches`):

```c
FILE *in = stdin;                    /* default: standard input   */
in = fopen(argv[1], "r");            /* returns NULL on failure    */
fprintf(stderr, "logreport: cannot open %s\n", argv[1]);
fclose(in);                          /* only if you opened it      */
```

---

### Testing

Run the self-check from your project directory:

```bash
cd ~/CS265/project2
bash check_p2.bash
```

It compiles your file with the course flags. Then it checks the
report, the stderr messages, and the exit status on all five test
logs, plus the command-line cases. For each failure, it shows the
start of the difference.

**Passing every check is necessary but not sufficient.** Grading also
uses more logs that you haven't seen. Write small test logs of your
own for cases the public tests miss.

To compare outputs yourself:

```bash
./logreport tests/ties.log >| my.out 2>| my.err
diff tests/ties.out my.out
diff tests/ties.err my.err
```

The `>|` is there because the course `.bashrc` turns on `noclobber`.
A plain `>` would refuse to overwrite `my.out` the second time.

The Unix tools you already know make good sanity checks:

```bash
wc -l < tests/week.log          # should equal "Lines read" (the file ends in a newline)
grep -c ' 404 ' tests/week.log  # a lower bound on "4xx" (4xx also includes 401, 403, ...)
```

---

### Bonus (+10): No Fixed Limit, Using `malloc`

The base design breaks once a log has more than 100 distinct paths.
New paths stop being counted, and the report comes out wrong.
`tests/bonus_big.log` has over 1,500 distinct paths, and the popular
ones only appear after the first 150 lines.

For the bonus, remove the limit:

- Keep the path table on the heap. Start it small, and when it fills
  up, grow it with `realloc`. Doubling the size each time is typical.
- Give each path string exactly the space it needs. `malloc`
  `strlen(path) + 1` bytes, then `strcpy` the path in.
  **Don't use `strdup`.** It isn't part of C99, so under `-std=c99` it
  isn't declared, and gcc assumes it returns an `int`. That cuts the
  pointer down to 32 bits, and your program crashes.
- Add `#include <stdlib.h>` for `malloc`, `realloc`, and `free`.
- Check every `malloc` and `realloc` result for `NULL`.
- Before the program exits, `free` every string and then the table.
  Also **`fclose` the input file**. An unclosed `FILE` counts as
  memory still in use, and valgrind will flag it.
- Change the header comment line to `BONUS: attempted`. Without that
  change, the bonus isn't graded.

Your program must still produce exactly the same output on every
base test. Check the bonus with:

```bash
bash check_p2.bash --bonus
```

This runs `bonus_big.log`, then runs your program under
`valgrind --leak-check=full`. To pass, valgrind must report
`0 errors` and `All heap blocks were freed`.

The bonus earns points only if the `bonus_big.log` report is correct.
That's worth 5 points, and a clean valgrind run is worth 5 more.
A bonus attempt that breaks the base tests costs you more than it
earns. Get the base version passing first, and save a copy before you
start (`cp logreport.c logreport_base.c`).

---

### Grading Summary

| Component                | Points | How it's checked                                                    |
|--------------------------|-------:|---------------------------------------------------------------------|
| Compiles cleanly         | 10     | `gcc -Wall -Wextra -g -std=c99`. Warnings cost 5 points. **A file that doesn't compile earns 0 for the whole project.** These points also require that at least part of the report be correct on at least one log. |
| Report correctness       | 60     | 10 logs (5 public, 5 hidden). Each report is split into its 4 sections, and each section earns credit separately. |
| Malformed-line messages  | 10     | 1 point per log. The stderr output must match exactly, and that log's summary section must also be correct. |
| Command line             | 10     | Reading standard input, a file that can't be opened, and too many arguments |
| Code quality             | 10     | Header comment filled in; `sscanf` return values checked; every `%s` has a width; no writes past the end of an array; named constants instead of magic numbers; sensible functions and readable layout |
| **Bonus**                | +10    | `bonus_big.log` report correct (5), valgrind clean (5)              |

Because each section earns credit separately, a bug in one part of
the report costs only that section, on the logs where it shows up.
The hour tie rule is one example. A section whose format is merely
"close" earns nothing, so match the spacing exactly.

---

### Submission

Copy `logreport.c` to your own machine with `scp`, as you have in
previous labs this term:

```bash
scp <you>@tux.cs.drexel.edu:CS265/project2/logreport.c .
```

Then upload it to the **Project 2** assignment on Canvas. That one
file is your entire submission. Upload the source file, not the
compiled program.

Before you submit:

- [ ] The header comment has your name, Drexel userid, and date
- [ ] The `BONUS:` line says `attempted` or `not attempted`
- [ ] `gcc -Wall -Wextra -g -std=c99` gives no warnings **on tux**
- [ ] `bash check_p2.bash` passes **on tux**

## Your program will be compiled and graded on tux, so make sure it works there and not just on your laptop.
