# Activity 6: Draw the Memory

**CS-265: Advanced Programming Tools & Techniques** · In-class activity · 15 minutes · 5 points (effort)

Groups are fine; everyone submits their own answers on Canvas (text entry) by **11:59 PM today**.

For each part, **write your prediction down before you run anything.** A wrong prediction you can explain is worth more than a right guess.

## Setup (1 min)

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/activity6
cp ~/CS265/materials/activity6/* ~/CS265/activity6/
cd ~/CS265/activity6
```

Compile everything with the course compile line. The `-g` matters today, because gdb needs it:

```bash
gcc -Wall -Wextra -g -std=c99 file.c -o file
```

**Drawing memory.** Draw each variable as a labeled box holding its value. A pointer's box holds an arrow to the box it points at. To type a drawing on Canvas, write each variable on one line, like this:

```
x [ 10 ]
p [ -> x ]
```

## Part 1: Draw it (4 min)

Read `boxes.c` with its line numbers showing. Don't run it yet.

```bash
cat -n boxes.c
```

1. Draw `x`, `y`, and `p` as they are **just before line 12** (`p = &y;`) runs.
2. Draw them again at the end, just before the `printf` on line 15.
3. **Predict** the line the program prints. Then compile and run it:

   ```bash
   gcc -Wall -Wextra -g -std=c99 boxes.c -o boxes
   ./boxes
   ```

## Part 2: Check it with gdb (5 min)

gdb can stop your program at a line and show you what's in memory. Start it:

```bash
gdb -q ./boxes
```

Type these commands at the `(gdb)` prompt, one at a time:

```
break 12
break 15
run
```

If gdb asks **`Enable debuginfod for this session? (y or [n])`**, type `n` and press Enter.

The program stops at line 12. A breakpoint stops the program **before** that line runs. Now type:

```
print x
print y
print &x
print p
print *p
```

Then type `continue`. The program stops at line 15. Type `print y`, `print &y`, `print p`, and `print *p`. Finally, type `continue` once more to let the program finish, then `quit`. If gdb asks `Quit anyway? (y or n)`, type `y`.

1. At line 12, how do the values of `&x` and `p` compare? What does that tell you `p` holds?
2. At line 15, which variable does `p` point to now? How can you tell from gdb's output?
3. Did gdb agree with both of your drawings from Part 1? If not, what did you get wrong?

## Part 3: A swap that works (3 min)

In Lab 6, `swap(int a, int b)` couldn't change `main`'s variables, because it got copies. `swap.c` passes **addresses** instead: `swap(&x, &y)`.

The starter compiles with two `unused parameter` warnings. Edit `swap.c` and write the three-line body of `swap` so the program prints `x = 7, y = 3`. Use `*a` and `*b`. Compile with the course compile line until there are no warnings, then run it.

If it prints `x = 3, y = 7`, you swapped the pointers `a` and `b` rather than the values they point at.

## Part 4: Pointers and arrays (2 min)

**Predict** lines A through E of `walk.c`, then compile and run it.

1. `p[i]` is shorthand for `*(p + i)`, so line B could have been written `p[2]`. After `int *p = a;`, which address does `p` hold?
2. Lines F and G print the addresses of `a[0]` and `a[1]` in hexadecimal. How far apart are they in bytes, and why that number?

## Submit on Canvas

1. Part 1: your two drawings, your prediction, and the actual output.
2. Part 2: your answers to questions 1–3.
3. Part 3: your `swap` function.
4. Part 4: your predictions, the actual output for lines A through E, and your answers to questions 1 and 2.
