# Lab 4: From Source to Executable

**CS-265: Advanced Programming Tools & Techniques** · 10 questions · 100 points · Due **Sunday 11:59 PM**

In lecture you saw that `gcc hello_world.c` is really four steps: **preprocess → compile → assemble → link**. In this lab you'll stop `gcc` after each step, look at what it produced, and then use that knowledge to tell *which step* an error came from. That last skill is the point: an error you can place is an error you can fix.

## Setup

```bash
cd ~/CS265/materials && git pull
mkdir ~/CS265/lab4
cp ~/CS265/materials/lab4/* ~/CS265/lab4/
cd ~/CS265/lab4
mv lab4_template.txt lab4.txt
```

Answer in `lab4.txt`. For each question, paste the **exact command** you ran and its **output**, plus any explanation asked for. You'll also edit three C files in Q6; you submit those too.

### The flags, in one place

| Flag | gcc stops after… | You get |
|---|---|---|
| `-E` | preprocessing | preprocessed C, printed to the terminal |
| `-S` | compiling | assembly, in `file.s` |
| `-c` | assembling | object code, in `file.o` |
| *(none)* | linking | an executable (`a.out`, or the name after `-o`) |

From Part 3 on, use the **course compile line**: `gcc -Wall -Wextra -g -std=c99`. `-Wall -Wextra` turn on warnings, `-g` keeps debugging info (you'll want it in a few weeks), and `-std=c99` picks the language version. Get in the habit now; every C lab from here on assumes it.

---

## Part 1: The preprocessor

## Q1. What the compiler really sees (10 pts)

Run:

```bash
wc -l hello_world.c
gcc -E hello_world.c | wc -l
```

1. Record both line counts. Where did all the extra lines come from?
2. Use `gcc -E` and `grep -w` to print the line that **declares** `printf`. Paste it. Why does the compiler need this line before it sees your call to `printf`?
3. `hello_world.c` contains the word `Kernighan`. Run `gcc -E hello_world.c | grep -c Kernighan`. What do you get, and why?

## Q2. `#define` and `#if` (10 pts)

Look at `freeze.c` first. **Predict** what the body of `main` will look like after preprocessing, then check (the `sed` just skips past the `stdio.h` part):

```bash
gcc -E freeze.c | sed -n '/int main/,$p'
```

1. Paste the output. What happened to `FREEZING_PT`?
2. Two `printf` calls disappeared. Explain why each one did. (They disappeared for slightly different reasons.)
3. Change `#define SHOW_EXTRA 0` to `1`, compile, and run `freeze.c`. Paste the output.
4. The `#if 0` block contains a `/* ... */` comment. Explain why wrapping that block in another `/* ... */` would **not** have commented it out cleanly. (Think back to `fleas.c` from Activity 4.)

---

## Part 2: Compiling and assembling

## Q3. Assembly, and a surprise (10 pts)

Stop after the compile step and look for the string and the function call:

```bash
gcc -S hello_world.c
grep -E 'string|call' hello_world.s
```

1. Paste the output.
2. Your C code calls `printf("Hello World\n")`. What function does the assembly actually call, and what happened to the `\n`? 
3. Explain why the compiler is allowed to do this. (Hint: what does `puts` always add to the end of its output? Look at `man 3 puts`.)

## Q4. Object code is not a program (10 pts)

```bash
gcc -c hello_world.c
gcc hello_world.o -o hello_world
file hello_world.o hello_world
ls -l hello_world.o hello_world
```

1. Paste the output of `file` and `ls -l`. Name two differences between the `.o` and the executable.
2. Try `./hello_world.o`. What happens?
3. Run `nm hello_world.o`. `nm` lists the *symbols* (names) in an object file: `T` means "defined here," `U` means "used here but **undefined**; someone else has to supply it." Paste the output. Which symbol is `U`, and who supplies it when you link?

---

## Part 3: Linking

`main.c` calls a function, `c_to_f`, that lives in `temp.c`. `temp.h` holds its declaration. (The `#ifndef TEMP_H` / `#define TEMP_H` / `#endif` lines in `temp.h` are an *include guard*; they stop the header being pasted in twice. You don't need to do anything with them.)

## Q5. Separate compilation (10 pts)

Build the program one file at a time:

```bash
gcc -Wall -Wextra -g -std=c99 -c temp.c
gcc -Wall -Wextra -g -std=c99 -c main.c
gcc -Wall -Wextra -g -std=c99 main.o temp.o -o tconv
./tconv
```

1. Paste the output of `./tconv`.
2. Run `nm main.o` and `nm temp.o`. Paste both. Explain, using `T` and `U`, how the linker knows that `main.o`'s call to `c_to_f` should go to the code in `temp.o`.

## Q6. Add a function (10 pts)

1. Add a function `f_to_c` to `temp.c` that converts Fahrenheit to Celsius. Use `FREEZING_PT` rather than typing `32`.
2. Add its declaration to `temp.h`.
3. Add one line to `main.c` that prints `98.6 F = 37.0 C` by calling `f_to_c(98.6)`.
4. Rebuild `tconv` the same way as Q5 and paste the output.

Then answer:

5. Suppose you later fix a bug **inside `f_to_c` only** (`temp.c` changes; nothing else does). What is the shortest list of commands that rebuilds `tconv` correctly? Why don't you need to recompile `main.c`?
6. Suppose instead you edit **`temp.h`**. Which `.o` files are now out of date, and why?

## Q7. A linker error (10 pts)

Try to link without `temp.o`:

```bash
gcc -Wall -Wextra -g -std=c99 main.o -o tconv2
```

1. Paste the error.
2. Which program printed it? (Look at the start of the lines, and at the last line.) Which of the four steps failed?
3. Why did `gcc -c main.c` succeed back in Q5, even though `main.c` doesn't contain `c_to_f`?

## Q8. Why prototypes matter (10 pts)

Make a copy of `main.c` with the `#include "temp.h"` line removed, and build it:

```bash
grep -v 'temp.h' main.c > noproto.c
gcc -Wall -Wextra -g -std=c99 -c noproto.c
gcc -Wall -Wextra -g -std=c99 noproto.o temp.o -o noproto
./noproto
```

1. Did it compile? Did it link? Paste the **first** warning and the program's output.
2. The output is wrong. Without a declaration, what does the compiler *assume* `c_to_f` returns? (The warnings tell you.)
3. The linker matched the call to `c_to_f` with the function in `temp.o` just fine. Why didn't the linker notice the mismatch? (Look at what `nm` showed you in Q5: does a symbol carry its type?)

**Moral:** read warnings. This program compiled, linked, and ran, and it's still wrong.

## Q9. Libraries (10 pts)

`hyp.c` calls `sqrt` from the math library. Try, in order:

```bash
gcc -Wall -Wextra -g -std=c99 hyp.c -o hyp
gcc -Wall -Wextra -g -std=c99 -lm hyp.c -o hyp
gcc -Wall -Wextra -g -std=c99 hyp.c -o hyp -lm
./hyp
```

1. Paste the error from the first command. Which step failed?
2. `#include <math.h>` is right there in the file. Why isn't that enough? (What's in a header, and what's in a library?)
3. The second command fails too, and the third works. The linker reads its inputs left to right and only takes from a library what's *already* been asked for. Use that to explain the difference.

---

## Part 4: Error triage

## Q10. Which step broke? (10 pts)

Each of `err1.c` through `err4.c` has one problem. For **each** file, run both:

```bash
gcc -Wall -Wextra -g -std=c99 -c errN.c
gcc -Wall -Wextra -g -std=c99 errN.c -o errN
```

and fill in the table in your template:

- the key line of the error message,
- which step failed: **preprocess, compile, or link**,
- the evidence (*who* printed it, and did `-c` succeed?),
- the one-line fix.

Two of the four pass `gcc -c` cleanly. That's a big clue.

---

## Submitting

1. Copy your files back to your own computer:

   ```bash
   scp <you>@tux.cs.drexel.edu:CS265/lab4/{lab4.txt,temp.c,temp.h,main.c} .
   ```

2. Upload `lab4.txt`, `temp.c`, `temp.h`, and `main.c` to the **Lab 4** assignment on Canvas.

Late policy: −10 / −20 / −30 per day; not accepted after 4 days.
