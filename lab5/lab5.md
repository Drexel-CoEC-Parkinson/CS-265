# Lab 5: Types, I/O, and Your First C Programs

**CS-265: Advanced Programming Tools & Techniques** · 10 questions · 100 points · Due **Sunday 11:59 PM**

So far you've compiled C. Now you'll write it. The first half of this lab uses small programs to show how C's types behave, including the places where C does something legal but surprising. The second half has you write five short programs that read input safely and print exactly what's asked.

## Setup

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/lab5
cp ~/CS265/materials/lab5/* ~/CS265/lab5/
cd ~/CS265/lab5
mv lab5_template.txt lab5.txt
```

Answer in `lab5.txt`. For each question, paste the **exact command** you ran and its **output**, plus any explanation asked for.

**Predict first.** Where a question says PREDICT, write your prediction in `lab5.txt` *before* you run anything. A wrong prediction loses no points. A blank one does.

Compile everything with the **course compile line**:

```bash
gcc -Wall -Wextra -g -std=c99 file.c -o file
```

### Rules for the programs you write (Q7–Q10)

- **Zero warnings** with the course compile line.
- **A header comment** at the top of each file with your name and what the program does.
- **Consistent indentation.**
- **Use `fgets` + `sscanf` for input**, the pattern in `readint.c`. Don't call `scanf` directly. Q6 shows why.
- **Print no prompts.** Your output must match the examples exactly, because these programs are graded by feeding them input and comparing the output.

### C syntax you'll need

If you know Python or Java, this is mostly new punctuation.

```c
if (x > 0) {                       /* the parentheses are required */
    printf("positive\n");
} else if (x < 0) {
    printf("negative\n");
} else {
    printf("zero\n");
}

for (int i = 0; i < n; i++) {      /* start; keep going while; step */
    printf("%d\n", i);
}

while (x > 0) {                    /* test first */
    x = x / 2;
}

int values[100];                   /* 100 ints: values[0] ... values[99] */
values[0] = 7;
```

C doesn't check array bounds. `values[100]` compiles, then quietly touches memory that isn't yours. Keeping your index in range is your job.

---

## Part 1: Types

## Q1. Sizes and limits (10 pts)

1. **PREDICT** the size in bytes that `sizes.c` will print for each of the 7 types, using the "Size on Tux" tables from lecture.
2. Compile and run `sizes.c`. Paste the output. Note any predictions that were wrong.
3. Explain the last two lines of output. Why did adding 1 to a `short` give a negative number? Why did subtracting 1 from an `unsigned int` give a huge one?
4. An `int` is 4 bytes here, but the C standard only guarantees 2. Why does `sizes.c` use `sizeof` instead of assuming a size? Give one way a program could break if it were moved to a machine where `int` is 2 bytes.

## Q2. Integers and floats don't follow the same rules (10 pts)

1. **PREDICT** lines A through J of `arith.c`.
2. Compile and run it. Paste the output.
3. Explain why A is `0` but B is `18`.
4. Explain the difference between F and G. Both have `(double)` in them.
5. Line H prints `0`, which means false. Use line I to explain why. What should you write instead of `==` to compare two floating-point values?
6. Line J stored `16777217.0` in a `float` and printed something else. Why? (Think about how many decimal digits of precision a `float` has.)
7. The last line of `arith.c` has a bug: `total` is 17 and `n` is 5, so the average should be `3.40`. Fix that line **without changing the types of `total` or `n`**. Paste your fixed line and the new output.

## Q3. Characters are small integers (10 pts)

1. **PREDICT** lines A through K of `chars.c`.
2. Compile and run it. Paste the output.
3. Line D prints a capital letter. Why does subtracting 32 do that? Why is `c - ('a' - 'A')` better code than `c - 32`?
4. Line J prints `4`, but `"abc"` has three letters. What's the fourth `char`?
5. Write a single C expression that turns a digit character stored in `char c` (such as `'8'`) into the integer it represents (`8`). Don't use any library functions.

---

## Part 2: Conditions and loops

## Q4. Predict the logic (10 pts)

C has no separate true or false in these expressions: comparisons give `1` or `0`, and any nonzero value counts as true.

`exprs.c` sets `i = 2`, `j = 1`, and `k = 0`.

1. **PREDICT** lines 1 through 9.
2. Compile `exprs.c` with the course compile line, then run it. It produces two warnings on purpose. Paste the warnings and the output.
3. Line 5 is `!j < i`. Rewrite it with parentheses to show how C actually groups it.
4. Line 8 is `3 > 2 > 1`, which is true in math. Why is it `0` in C?
5. Line 9 divides by `k`, which is `0`. Why doesn't the program crash?

Now `loops.c`. Run it as `./loops 1`, `./loops 2`, and so on.

6. **PREDICT** the output of loops 1, 2, and 3. Then run them and paste the output.
7. Loop 2's test is false from the start, but its body still ran. Why?
8. Loop 3 prints a single number. Find the bug, and explain why the compiler's warning points at it.
9. Loop 4 never ends. Run it safely with `./loops 4 | head -10` and paste the output. Why does it never reach 0?

---

## Part 3: Input and output

## Q5. `printf` is a formatting language (10 pts)

1. **PREDICT** lines A through M of `fmt.c`. Spaces count, and the bars show exactly where each field starts and ends.
2. Compile and run it. Paste the output.
3. Line L has a width of 3, but it printed 6 digits. What does that tell you about what width means?
4. Write one `printf` call that prints exactly this, using `%` conversions for the numbers `31` and `2.5` and a `\n` at the end. The field for `2.5` is 6 characters wide:

   ```
   0x1f|  2.50|
   ```

5. Compile `fmtbad.c` and paste the warnings. Run it and paste the output. Each `printf` here breaks the same rule. What's the rule, and why can't you trust *any* of the numbers it printed? Your output might not match a classmate's, and that's part of the answer.

## Q6. Why we don't use `scanf` for input (10 pts)

`scanf` returns how many items it successfully stored, or `EOF` if input ended first.

1. **PREDICT** what `scan.c` prints for each input below. Then compile it, run these, and paste the output:

   ```bash
   echo '12 34' | ./scan
   echo '12 x' | ./scan
   echo 'x' | ./scan
   ./scan < /dev/null
   ```

2. Why are `a` and `b` passed as `&a` and `&b`, while `printf` takes plain `a` and `b`? (One sentence. We'll do this properly next week.)
3. Now run `scanloop.c`, using `head` so it can't run forever:

   ```bash
   echo '1 2 x 3' | ./scanloop | head -5
   ```

   Paste the output. What happened when `scanf` reached the `x`, and why did the loop never finish?
4. Compile `readint.c`, which does the same job with `fgets` + `sscanf`, and run:

   ```bash
   printf '1\n2\nx\n3\n' | ./readint
   ```

   Paste the output. Why does this version get past the `x`? What are the `line` buffer and `sscanf` doing that `scanf` alone couldn't?

---

## Part 4: Write your own

For testing: `./prog < file` feeds a file to your program as input. At the keyboard, press **Ctrl-D** at the start of a line to signal end of input.

One detail for reading floating-point values: `printf` uses `%f` for a `double`, but `sscanf` needs `%lf`.

## Q7. `leap.c` (10 pts)

Read one year from a line of input. Write and use a function `int is_leap(int year)` that returns nonzero for a leap year.

A year is a leap year if it's divisible by 4, except that years divisible by 100 aren't, except that years divisible by 400 are.

```
$ echo 2024 | ./leap
2024 is a leap year
$ echo 1900 | ./leap
1900 is not a leap year
$ echo abc | ./leap
Not a year
```

If the input isn't a number, print `Not a year` and return `1` from `main`.

In your template, fill in the test table for 1900, 2000, 2024, 2025, and 2100. For each year, write down the answer you expect *from the rule* before you run the program.

## Q8. `ult.c` and `urt.c` (10 pts)

Each program reads a height from one line of input and prints a triangle using nested loops. `ult` is an upper-left triangle, and `urt` is an upper-right triangle.

```
$ echo 4 | ./ult          $ echo 4 | ./urt
****                      ****
***                        ***
**                          **
*                            *
```

- Print no spaces after the last `*` on a line.
- If the input isn't a number from 1 to 20, print `Height must be 1 to 20` and return `1` from `main`.

Check for trailing spaces with `echo 4 | ./urt | cat -A`. Each line should end in `*$`.

In your template, write down the formula for how many spaces and how many stars row `r` of `urt` has, with rows numbered from 0.

## Q9. `readlines.c` (10 pts)

Read one number per line until end of input **or** a blank line. Then print the count, minimum, maximum, and mean. Use `double` values.

```
$ ./readlines < numbers.txt
Count: 4
Min: -2.00
Max: 9.50
Mean: 3.62
$ ./readlines < blank.txt
Count: 1
Min: 4.00
Max: 4.00
Mean: 4.00
$ ./readlines < messy.txt
skipping: banana
Count: 2
Min: 4.00
Max: 9.50
Mean: 6.75
$ ./readlines < /dev/null
No numbers
```

- **Write the read loop yourself.** `readint.c` is your model.
- **Use no array, and no "magic" starting values** such as `min = 99999`. The first number you read sets both `min` and `max`.
- Negative numbers are allowed.
- A line that isn't a number prints `skipping: ` followed by the line, then the program moves on.
- A blank line has `'\n'` as its first character: `line[0] == '\n'`.

In your template, explain why starting with `min = 0` would give a wrong answer, and give an input that shows it.

## Q10. `rev-array.c` (10 pts)

Read integers, one per line, using the same stopping and skipping rules as Q9. Then print them in reverse order, one per line.

```c
#define MAX 100
```

- Store the values in an array of size `MAX`.
- Build the reversed values in a **second** array of size `MAX`, then print that array.
- If a 101st value arrives, print `Stopped at 100 values`, stop reading, and print the 100 values you have, reversed. Don't let the program write past the end of the array.

```
$ printf '1\n2\n3\n' | ./rev-array
3
2
1
$ ./rev-array < many.txt | head -3
Stopped at 100 values
100
99
```

In your template, answer: what could go wrong if you removed the check for 100 values and fed in `many.txt`? Would the compiler have warned you?

---

## Submitting

1. Copy your files back to your own computer:

   ```bash
   scp <you>@tux.cs.drexel.edu:CS265/lab5/{lab5.txt,leap.c,ult.c,urt.c,readlines.c,rev-array.c} .
   ```

2. Upload `lab5.txt`, `leap.c`, `ult.c`, `urt.c`, `readlines.c`, and `rev-array.c` to the **Lab 5** assignment on Canvas.

Late policy: −10 / −20 / −30 per day; not accepted after 4 days.
