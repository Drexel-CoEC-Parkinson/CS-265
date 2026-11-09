# Activity 5: Branches, Loops, and Functions

**CS-265: Advanced Programming Tools & Techniques** · In-class activity · 15 minutes · 5 points (effort)

Groups are fine; everyone submits their own answers on Canvas (text entry) by **11:59 PM today**.

For each part, **write your prediction down before you run anything.** A wrong prediction you can explain is worth more than a right guess.

## Setup (1 min)

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/activity5
cp ~/CS265/materials/activity5/* ~/CS265/activity5/
cd ~/CS265/activity5
```

(If your repo folder has a different name, such as `CS-265`, use what exists for you.)

Compile everything with the course compile line:

```bash
gcc -Wall -Wextra -g -std=c99 file.c -o file
```

## Part 1: The order of `if` tests

`order.c` gives a letter grade for a score of 95. **Predict** what it prints, then compile and run it.

- Why did it print what it printed?
- Reorder the tests so a 95 prints `A`, and a 65 would still print `D`. Which test has to come first?

## Part 2: `break` and `continue`

**Predict** the exact output of `skip.c`, then compile and run it.

- Which numbers did `continue` skip, and why?
- Why does the output stop where it does?

## Part 3: What can a function change?

**Predict** the line that `twice.c` prints, then compile and run it.

- `twice` changed `x`. Why didn't `a` change?

## Part 4: A function that forgets to return

`sign` should return `1`, `-1`, or `0`. Compile `sign.c` with the course compile line.

- What does the warning say? Which input reaches the end of `sign` without a `return`?
- Run it. What does `sign(0)` print? Compare with a neighbor. Why can't you trust that number?
- Fix `sign` so the warning goes away and `sign(0)` prints `0`.

## Submit on Canvas

1. Part 1: what `order.c` printed, why, and your reordered tests.
2. Part 2: your prediction, the actual output, and your two answers.
3. Part 3: your prediction, the actual output, and why `a` didn't change.
4. Part 4: the warning text, what `sign(0)` printed, and your fixed `sign` function.
