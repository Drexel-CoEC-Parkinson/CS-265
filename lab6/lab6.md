# Lab 6: Branches, Functions, and Arrays

**CS-265: Advanced Programming Tools & Techniques** · 10 questions · 100 points · Due **Sunday 11:59 PM**

Lab 5 had you writing `if` statements, loops, and an array inside `main`. This lab splits programs into functions. You'll see what a function can and can't change, how arrays behave when you pass them to a function, and how a program reads its command-line arguments. Then you'll write three programs and fix a fourth.

## Setup

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/lab6
cp ~/CS265/materials/lab6/* ~/CS265/lab6/
cd ~/CS265/lab6
mv lab6_template.txt lab6.txt
```

Answer in `lab6.txt`. For each question, paste the **exact command** you ran and its **output**, plus any explanation asked for.

**Predict first.** Where a question says PREDICT, write your prediction in `lab6.txt` *before* you run anything. A wrong prediction loses no points. A blank one does.

Compile everything with the **course compile line**:

```bash
gcc -Wall -Wextra -g -std=c99 file.c -o file
```

Some starter programs produce warnings on purpose. The questions ask about them. `arrstats.c` also warns until you write its functions in Q9.

---

## Part 1: Branches

## Q1. `switch` and `break` (10 pts)

`switch.c` calls `describe(n)` for `n` from 0 to 5.

1. **PREDICT** all six lines of output.
2. Compile `switch.c` and paste the warning, including the `note:` line under it. Run it and paste the output.
3. Why does `describe(1)` print two words? Which line does the warning point at?
4. Cases 3 and 4 share code with no `break` between their labels, but the compiler doesn't warn about that. Why is that one fine?
5. Fix `switch.c` so `describe(1)` prints only `one`. Recompile. Paste your fixed `case 1` and confirm the warning is gone.

---

## Part 2: Functions

## Q2. Scope (10 pts)

`scope.c` has a global `count`, a local `count` in `main`, and another `count` inside a loop.

1. **PREDICT** the output.
2. Compile and run it. Paste the output.
3. `local` prints `1` every time, but `calls` keeps growing. What does `static` change?
4. After `main` declares its own `count = 5`, the third call to `bump` still changes the global. Why doesn't `bump` see `main`'s `count`?
5. Add `printf("%d\n", i);` right after the `for` loop's closing brace and compile. Paste the error. Why is `i` gone? Then remove the line.

## Q3. Pass-by-value (10 pts)

1. **PREDICT** the output of `byvalue.c`.
2. Compile it and paste the warning. Run it and paste the output.
3. Inside `swap`, the values are swapped. In `main`, they aren't. Explain why, using the word *copy*.
4. What is the compiler's warning about `reset` telling you?
5. Without pointers, how *could* `reset` give `main` a new value for `x`? Write the changed function and the changed call. (We'll fix `swap` properly next week.)

---

## Part 3: Arrays

## Q4. Array basics (10 pts)

1. **PREDICT** lines A through E of `arrays.c`.
2. Compile and run it. Paste the output.
3. `a` has 5 elements, but only 3 values are listed. What are the other two, and why?
4. Line B prints a size in bytes. Explain why `sizeof b / sizeof b[0]` in line C gives the number of elements.
5. Add the line `a = b;` just above `return 0;` in `main` and compile. Paste the error. How would you copy one array into another instead? Then remove the line.
6. In the same spot, add `a[5] = 99;` instead, then compile and run. Did the compiler or the program stop you? Is that line correct? Explain. Then remove the line.

## Q5. Passing arrays to functions (10 pts)

1. **PREDICT** the output of `arrfunc.c`.
2. Compile it and paste the warning. Run it and paste the output.
3. In Q3, a function couldn't change `main`'s `x`. Here, `fill` changed `main`'s array. What's different about what the function received? (A sentence about what you observe is enough. Next week explains why.)
4. Why do `fill` and `sum` need the `n` parameter? Why couldn't they use `sizeof` to work out the length?
5. `main` prints `16` and `show_size` prints `8` for the same array. Which number is the array's size?

---

## Part 4: Command-line arguments

`main` can be written as `int main(int argc, char *argv[])`. `argc` is the number of words on the command line, including the program name. `argv` is an array of those words, as strings.

## Q6. `argc` and `argv` (10 pts)

1. Compile `args.c`. **PREDICT** what it prints for each command, then run them and paste the output:

   ```bash
   ./args
   ./args one two
   ./args "one two" three
   ./args 3 + 4
   ```

2. Now run these two and paste the output. Who turned `*.c` into a list of names: your program, or the shell?

   ```bash
   ./args *.c
   ./args '*.c'
   ```

3. In `./args 3 + 4`, `argv[1]` is `"3"`. Why can't you do arithmetic on it directly? Write the one line that stores it as an `int` in a variable `n`. (Q7 needs this.)

---

## Part 5: Write your own

### Rules for Q7–Q10

- **Zero warnings** with the course compile line.
- **A header comment** at the top of each file with your name and what the program does.
- **Consistent indentation.**
- Read keyboard input with **`fgets` + `sscanf`**, as in Lab 5. To read a number from `argv`, use `sscanf` on the argument directly.
- **Print no prompts.** Your output must match the examples exactly.

## Q7. `power.c` (10 pts)

Write a program that takes a base and an exponent on the command line and prints the base raised to that power. Write and use a function `long ipow(long base, int exp)` that computes it with a loop. Don't use `pow` from `math.h`.

```
$ ./power 2 10
2^10 = 1024
$ ./power -3 3
-3^3 = -27
$ ./power 5 0
5^0 = 1
$ ./power 2
Usage: power BASE EXP
$ ./power 2 x
Not a number
$ ./power 2 -1
Exponent must be 0 or more
```

- If there aren't exactly two arguments, print `Usage: power BASE EXP` and return `1`.
- If `sscanf` can't read a number from either argument, as with `x`, print `Not a number` and return `1`. You don't need to reject arguments like `2.5` or `3abc`. `sscanf` reads the leading `2` or `3`, and that's acceptable.
- If the exponent is negative, print `Exponent must be 0 or more` and return `1`.
- Otherwise, print the result in the format shown and return `0`.
- Read the base with `%ld`, because it's a `long`. Read the exponent with `%d`.

In your template, paste the output of `./power 2 62` and `./power 2 64`. Explain the second one. (Lab 5, Q1.)

## Q8. `grades.c` (10 pts)

Read one score per line until end of input **or** a blank line. For each score, print it with its letter grade. At the end, print how many of each grade there were.

Write and use a function `char letter_grade(int score)`: 90 and up is `A`, 80–89 is `B`, 70–79 is `C`, 60–69 is `D`, and below 60 is `F`.

```
$ ./grades < scores.txt
95 A
82 B
skipping: banana
out of range: 105
71 C
58 F
90 A
A:2 B:1 C:1 D:0 F:1
```

- A line that isn't a number prints `skipping: ` followed by the line.
- A score below 0 or above 100 prints `out of range: ` followed by the score, as in `out of range: 105`, and isn't counted.
- **Count the grades with a `switch` on the letter.**
- Always print the summary line, in exactly the format shown, even if there were no scores.

In your template, list the scores you used to test the edge of each grade, and explain why the order of your `if` tests in `letter_grade` matters. (Activity 5, Part 1.)

## Q9. `arrstats.c` (10 pts)

`arrstats.c` comes with `main` already written. It reads integers into an array, then calls five functions. It reads input by the same rules as Lab 5's `rev-array.c`: one number per line, a non-number prints `skipping:`, and a blank line, end of input, or the 100-value limit stops the reading. **Write those five functions. Don't change `main` or the prototypes.** Do fill in your name in the header comment.

The starter compiles now, but with `unused parameter` warnings. Each warning goes away when you write that function, and the finished file must have none.

| Function | Does |
|---|---|
| `int find_max(int a[], int n)` | Returns the largest of the `n` values |
| `double mean(int a[], int n)` | Returns their average |
| `int count_above(int a[], int n, double limit)` | Returns how many values are strictly greater than `limit` |
| `void reverse(int a[], int n)` | Reverses the values **in place**, with no second array |
| `void print_array(int a[], int n)` | Prints the values on one line, separated by single spaces, then a newline. No space after the last value. |

```
$ ./arrstats < nums.txt
Count: 5
Max: 9
Mean: 4.40
Above mean: 2
Reversed: 2 6 1 9 4
```

- `find_max` must work when every value is negative. Don't start the maximum at 0.
- `mean` must return the exact average. Watch out for integer division.
- Check for a trailing space with `./arrstats < nums.txt | cat -A`. The last line should end in `4$`.

In your template, explain how many swaps `reverse` needs for `n` values, and why. What would happen if it swapped `n` times instead?

## Q10. `bugs.c` (10 pts)

`bugs.c` should print `Total: -30` and `Max: -1`. It has two bugs.

1. Compile and run it with the course compile line. Paste the output. Did the compiler warn you?
2. Recompile with **AddressSanitizer**, a tool that checks memory accesses while the program runs:

   ```bash
   gcc -Wall -Wextra -g -std=c99 -fsanitize=address bugs.c -o bugs
   ./bugs
   ```

   The report is long. Near the top, find the line containing `ERROR: AddressSanitizer`, and below it the first line that names `bugs.c` and a line number. Paste both lines. Which line of `bugs.c` is it, and what's wrong with it?
3. Fix both bugs. The second one isn't a memory bug, so AddressSanitizer won't find it. Think about Lab 5, Q9. Rebuild with the course compile line, run it, and paste the correct output. Then rebuild once more with `-fsanitize=address` and run it, to confirm that AddressSanitizer reports nothing.
4. Explain the second bug.

---

## Submitting

1. Copy your files back to your own computer:

   ```bash
   scp <you>@tux.cs.drexel.edu:CS265/lab6/{lab6.txt,power.c,grades.c,arrstats.c,bugs.c} .
   ```

2. Upload `lab6.txt`, `power.c`, `grades.c`, `arrstats.c`, and `bugs.c` to the **Lab 6** assignment on Canvas.

Late policy: −10 / −20 / −30 per day; not accepted after 4 days.
