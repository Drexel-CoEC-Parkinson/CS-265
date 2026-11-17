# Lab 7: Pointers, Strings, and the Heap

**CS-265: Advanced Programming Tools & Techniques** · 10 questions · 100 points · Due **Sunday 11:59 PM**

This lab puts pointers to work. You'll use them to return more than one value from a function, to work with C strings, and to manage memory you get from `malloc`. You'll also meet **valgrind**, a tool that watches your program run and reports memory mistakes that the compiler can't see.

## Setup

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/lab7
cp ~/CS265/materials/lab7/* ~/CS265/lab7/
cd ~/CS265/lab7
mv lab7_template.txt lab7.txt
```

Answer in `lab7.txt`. For each question, paste the **exact command** you ran and its **output**, plus any explanation asked for.

**Predict first.** Where a question says PREDICT, write your prediction in `lab7.txt` *before* you run anything. A wrong prediction loses no points. A blank one does.

Compile everything with the **course compile line**:

```bash
gcc -Wall -Wextra -g -std=c99 file.c -o file
```

Keep the `-g`. gdb and valgrind need it to show line numbers.

### Running valgrind

```bash
valgrind --leak-check=full ./program
```

Your program runs as usual, only slower, and valgrind prints its report around your program's output. Every valgrind line starts with a number between `==` signs, such as `==4821==`. The number is a process ID that changes on every run, so ignore it. To give the program input, redirect it as usual: `valgrind --leak-check=full ./program < file.txt`.

Near the end of the report are two **summary lines**. On a clean run, they look like this:

```
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If memory leaked, the first summary line is replaced by a `LEAK SUMMARY:` section. When a question asks for the summary lines, paste the `All heap blocks were freed` line (or the `definitely lost:` line from `LEAK SUMMARY`) and the `ERROR SUMMARY` line.

---

## Part 1: Pointers

## Q1. Pointer warm-up (10 pts)

1. **PREDICT** lines A through H of `ptrs.c`.
2. Compile and run it. Paste the output.
3. Lines C and D print different sizes, but `p` and `q` were declared on the same line. What type is `q`, and why? How would you declare two pointers on one line?
4. Explain why A and B print different values. Which operator happens first in `*p + 1`?
5. Line G uses `p[1]` on a pointer, not an array. Which element of `a` does it read, and why?

## Q2. Returning two values (10 pts)

A function can `return` only one value. `divide` gives back two by writing through pointers.

1. **PREDICT** both lines of output from `divide.c`.
2. Compile and run it. Paste the output.
3. Why does `main` pass `&q` and `&r`, not `q` and `r`?
4. In your copy of `divide.c`, change the first call to `divide(17, 5, q, r);`. Compile it, but **don't run it**. gcc prints several warnings. Paste the first `warning:` line. In one sentence, what would `divide` do with those arguments? Then change the call back.

---

## Part 2: Strings

A C string is an array of `char` that ends with the null character `'\0'`. Functions like `strlen` and `printf("%s")` stop at the first `'\0'`.

## Q3. Strings and `string.h` (10 pts)

1. **PREDICT** lines A through J of `strs.c`.
2. Compile and run it. Paste the output.
3. Explain why A and B differ, and why C and D differ.
4. After line F, `word[2]` still holds the `t` from `"cut"`. Why doesn't `printf` print it, and why does `strlen` agree? (Draw the first four boxes of `word` if it helps.)
5. Add `printf("%d\n", word == "kitten");` just above `return 0;` and compile. Paste the warning, then remove the line. What does `==` compare for two strings, and what should you use instead?

## Q4. A string that crashes (10 pts)

1. Compile `strbugs.c` and run it. Paste the output.

   You should see `HELLO`, then a crash message like `Segmentation fault (core dumped)`. A segmentation fault means the program touched memory it isn't allowed to touch.

2. Find the line with gdb:

   ```bash
   gdb -q ./strbugs
   ```

   At the `(gdb)` prompt, type `run`. If gdb asks `Enable debuginfod for this session? (y or [n])`, type `n`. When the program stops, type `bt` (backtrace), which lists the functions that were running, innermost first. Paste the lines that start with `#0` and `#1`. Then type `quit`, and `y` to confirm.

3. Which line crashed, and which call in `main` led there?
4. `first` and `second` hold the same kind of text, but only `second` crashes. Explain the difference between `char first[] = "hello";` and `char *second = "world";`.
5. Fix `strbugs.c` by changing **one line** so that it prints `HELLO` and `WORLD`. Paste the line you changed.

---

## Part 3: The heap

`malloc(n)` gives you `n` bytes of memory that last until you `free` them, and returns a pointer to the first byte, or `NULL` if there's no memory to give. The memory starts out holding garbage.

## Q5. `malloc` and `free` (10 pts)

1. Compile `heap.c`. **PREDICT** what `./heap 5` prints, then run it and paste the output.
2. `make_squares` calls `malloc(n * sizeof(int))`. Why multiply by `sizeof(int)`? What would go wrong with `malloc(n)`?
3. Why does `make_squares` check for `NULL`, and why does `main` check again?
4. `make_squares` returns a pointer, and `main` uses the memory after `make_squares` has returned. Why couldn't `make_squares` use a local array (`int result[100];`) and return `result`? Answer from what you know about local variables. Don't change the file.
5. Run `valgrind --leak-check=full ./heap 5` and paste the two summary lines. Is the program clean?

---

## Part 4: valgrind

## Q6. Finding a leak (10 pts)

`leaky.c` builds a greeting for each of three names in memory from `malloc`, then never frees any of them. Memory that's still allocated when the program ends, with nothing pointing to it, is a **leak**.

1. `make_greeting` asks for `strlen(name) + 8` bytes. `"Hello, "` is 7 characters. What is the 8th byte for?
2. **PREDICT** how many bytes leak in total for the names `Ada`, `Linus`, and `Grace`.
3. Compile and run `leaky` under valgrind. Under `LEAK SUMMARY:`, paste the line that starts with `definitely lost:`. Was your prediction right?
4. Fix the leak by adding **one line** to `leaky.c`. Paste the line you added and where you put it. Rerun valgrind and paste the two summary lines.

## Q7. Three memory bugs (10 pts)

`vbugs.c` has three memory bugs. It might print the right thing anyway, because memory bugs often hide.

1. Compile `vbugs.c`. gcc warns about one of the three bugs. Paste the warning.
2. Run `vbugs` under valgrind and paste the full report.
3. valgrind reports **four** errors. For each one, give:
   - the kind of error (the line right after the blank `==…==` line, such as `Invalid write of size 1`)
   - the line of `vbugs.c` it points to. Look for the **first** line in that error that names `vbugs.c`, such as `main (vbugs.c:11)`.
4. Two of the four errors come from the same bug. Which two, and what is the bug?
5. Fix all three bugs:
   - Allocate enough memory for the copy.
   - Don't use `copy` after it's freed.
   - Give `counts[2]` a value before it's read. Any value is fine.

   Rerun valgrind. Paste the two summary lines.

---

## Part 5: Write your own

### Rules for Q8–Q10

- **Zero warnings** with the course compile line.
- **Clean under valgrind** for the given input files: no errors, and `All heap blocks were freed`.
- **A header comment** with your name. In `strfuncs.c` and `minmax.c`, fill in the `Name:` line.
- **Consistent indentation.**
- **Print no prompts.** Output must match the examples exactly.
- Check the result of every `malloc` for `NULL`.

**Tip:** `strlen` returns a `size_t`, which is unsigned. A loop like `for (int i = 0; i < strlen(s); i++)` triggers a `-Wsign-compare` warning. Either declare `i` as `size_t`, or loop until you reach `'\0'`.

## Q8. `strfuncs.c` (10 pts)

`strfuncs.c` comes with `main` already written. It reads lines until end of input or a blank line, and calls four functions on each one. **Write those four functions. Don't change `main` or the prototypes.**

| Function | Does |
|---|---|
| `int count_char(const char *s, char c)` | Returns how many times `c` appears in `s`. Case matters: `'O'` doesn't count as `'o'`. |
| `void str_upper(char *s)` | Changes each lowercase letter in `s` to uppercase, in place. Use `toupper` from `<ctype.h>`. |
| `void str_reverse(char *s)` | Reverses `s` in place: `"abc"` becomes `"cba"` |
| `char *str_dup(const char *s)` | Returns a new copy of `s` in memory from `malloc`, or `NULL` if `malloc` fails |

- **Don't call `strdup`.** Write `str_dup` yourself with `malloc`, `strlen`, and `strcpy`.
- `main` frees each copy, so `str_dup` must return memory from `malloc`.
- `const char *s` means the function promises not to change the string `s` points to.
- The starter compiles with `unused parameter` warnings. They go away as you write each function.

```
$ ./strfuncs < phrases.txt
Hello, World
  o's: 2
  upper: HELLO, WORLD
  reversed: dlroW ,olleH
pointers are fun
  o's: 1
  upper: POINTERS ARE FUN
  reversed: nuf era sretniop
racecar
  o's: 0
  upper: RACECAR
  reversed: racecar
No
  o's: 1
  upper: NO
  reversed: oN
x
  o's: 0
  upper: X
  reversed: x
```

Your output must match this exactly. Then check your program with valgrind on the same input.

In your template, explain why `str_dup` asks `malloc` for `strlen(s) + 1` bytes.

## Q9. `lines.c` (10 pts)

Write `lines.c` from scratch. It reads lines until end of input or a blank line, then prints them in **reverse order**, each with its original line number.

```
$ ./lines < poem.txt
3: And be one traveler, long I stood
2: And sorry I could not travel both
1: Two roads diverged in a yellow wood,
```

- Read with `fgets` into a `char line[100]` buffer, and remove the newline. `strfuncs.c` shows how in one line: `line[strcspn(line, "\n")] = '\0';`.
- Store the lines in an array of pointers, `char *lines[50]`. For each line, `malloc` exactly enough memory for a copy, copy the line into it, and store the pointer.
- Before the program ends, `free` every line you stored.
- If a 51st line arrives, print `Stopped at 50 lines`, stop reading, and print the 50 lines you have.
- No input at all prints nothing.

Test with `./lines < long.txt | head -3` as well. The first line should be `Stopped at 50 lines`. Check both files with valgrind.

In your template, explain why you can't just store `line` itself in `lines[count]`. What would every entry end up pointing to?

## Q10. `minmax.c` (10 pts)

`minmax.c` comes with `main` already written. It reads one number per line, prints `skipping:` for a line that isn't a number, and stops at a blank line, end of input, or 100 values. **Write the two functions. Don't change `main` or the prototypes.**

| Function | Does |
|---|---|
| `void min_max(int a[], int n, int *min, int *max)` | Stores the smallest of the `n` values in `*min` and the largest in `*max` |
| `int *copy_array(int a[], int n)` | Returns a new array from `malloc` holding a copy of the `n` values, or `NULL` if `malloc` fails |

```
$ ./minmax < nums.txt
skipping: seven
Min: -3
Max: 12
Original: 7 -3 12 0
Doubled: 14 -6 24 0
```

`min_max` must work when every value is negative. `main` doubles the values in the copy, so if `Original` changes too, `copy_array` isn't making a real copy.

In your template, explain why `min_max` takes `int *min` and `int *max` instead of returning a value.

---

## Submitting

1. Copy your files back to your own computer:

   ```bash
   scp <you>@tux.cs.drexel.edu:CS265/lab7/{lab7.txt,strbugs.c,leaky.c,vbugs.c,strfuncs.c,lines.c,minmax.c} .
   ```

2. Upload `lab7.txt`, your fixed `strbugs.c`, `leaky.c`, and `vbugs.c`, and your `strfuncs.c`, `lines.c`, and `minmax.c` to the **Lab 7** assignment on Canvas.

Late policy: −10 / −20 / −30 per day; not accepted after 4 days.
