# Activity 4: First Compile

**CS-265: Advanced Programming Tools & Techniques** · In-class activity · 15 minutes · 5 points (effort)

Groups are fine; everyone submits their own answers on Canvas (text entry) by **11:59 PM today**.

For each part, **write your prediction down before you run anything.** A wrong prediction you can explain is worth more than a right guess.

## Setup (1 min)

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/activity4
cp ~/CS265/materials/activity4/* ~/CS265/activity4/
cd ~/CS265/activity4
```
(Note - the folder /CS265/materials is where your repo is located. If your path name is different, such as "CS-265" or some variant, use what exists for you.)
You have four small programs: `hello_world.c`, `status.c`, `fleas.c`, and `specs.c`.

## Part 1: Compile and run, two ways

This is the program from the slides. Compile it both ways:

```bash
gcc hello_world.c
gcc hello_world.c -o hello
ls -l
```

Run each executable. Then answer:

- What does `ls -l` show about `a.out` and `hello` that's different from `hello_world.c`?
- Why do you have to type `./hello` and not just `hello`? (Think back to `PATH`.)

## Part 2: `main` returns to the shell

Look at `status.c`. It returns `3` from `main`. **Predict** what `echo $?` prints, then check:

```bash
gcc status.c -o status
./status
echo $?
```

Now edit `status.c` to `return 300;`, recompile, and run it again. **Predict first.** Then explain what you got. (Hint: the slide on `main` says the exit status is usually 8 bits.)

Finally, with `return 300;` still in place, what does this print, and why?

```bash
./status && echo ok || echo failed
```

## Part 3: The comment that ate my program

Look at `fleas.c` (it's the example from the Comments slide). **Predict** the exact output, then:

```bash
gcc fleas.c -o fleas
./fleas
```

Now compile again with warnings turned on:

```bash
gcc -Wall fleas.c -o fleas
```

What does the warning say, and what line is it pointing at? Fix the program using `//` comments so it prints `My cat has fleas`.

## Part 4: printf format specifiers

Look at `specs.c`. **Predict all nine lines** of output, then compile and run it.

- Which lines did you get wrong?
- Lines 4 and 5 print the same variable `c`. Why is the output different?

## Submit on Canvas

1. Part 1: your two answers.
2. Part 2: what `return 3` and `return 300` each gave for `$?`, your explanation of 300, and what the `&& ||` line printed.
3. Part 3: the warning text, and your fixed `printf`/comment lines.
4. Part 4: your predictions next to the real output, and your answer about lines 4 and 5.
