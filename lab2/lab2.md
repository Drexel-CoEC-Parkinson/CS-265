# CS-265 Lab 2 — The Bash Shell

**Due:** Sunday 11:59 PM on Canvas. Individual work. 100 points.

Lab 1 got you onto tux and into vim. This lab is about the thing you have been typing into all along: **bash**. By the end you should understand what happens between pressing Enter and seeing output — how the shell finds a command, how it expands what you typed, where the three standard streams go, and how to connect commands to each other.

Nearly everything here comes from the Week 2 lecture, *Introduction to the Bash Shell*; the few tools that don't are explained where they appear. Keep the slides open while you work.

Record your answers in `lab2.txt` (Part 0 shows you how to create it from the supplied template). Paste commands exactly as you ran them and output exactly as it printed.

## Learning goals

- Distinguish shell builtins from disk utilities, and explain how the shell resolves a command name.
- Set and dereference shell variables; use command substitution to put a command's output into a line.
- Control when the shell interprets metacharacters, using weak quoting, strong quoting, and the escape character.
- Expand filenames with the wildcards `*`, `?`, `[list]`, and `[!list]`.
- Redirect stdout, stderr, and stdin independently, and explain why redirection order matters.
- Connect commands with pipes to answer a question about a data file.
- Read an exit status and use `&&`, `||`, and subshells.

---

## Part 0 — Setup

Pull the latest materials and make a working directory for this lab:

```
cd ~/CS265/materials
git pull
mkdir ~/CS265/lab2
cp -r lab2/* ~/CS265/lab2/
cd ~/CS265/lab2
ls
```

Note the `-r` on `cp` — this lab ships a subdirectory, `gallery/`, and a plain `cp` would skip it without telling you.

There are now two directories named `lab2`. The one in `~/CS265/materials` is the course's copy; leave it alone so `git pull` always works. `~/CS265/lab2` is yours, and all of your work goes there.

You should have: `gallery/` (a folder of exported photos and a toy C program), `visits.log` (a study-room door log — one username per visit, 40 lines), `lab2_template.txt`, and `README.md`.

As in Lab 1, rename the template to the name you will submit:

```
mv lab2_template.txt lab2.txt
```

Open `lab2.txt` in vim and fill it in as you go. The file you hand in is `lab2.txt`.

---

## Part 1 — What is a command?

Slide 9 claims some commands are handled by the shell itself and some are programs on disk. Let's check.

**Q1** Run each of these and record the output:

```
type cd
type echo
type -a ls
type -a echo
```

Then run both of these and record what each prints:

```
echo -e "one\ttwo"
/usr/bin/echo -e "one\ttwo"
```

Answer three things. (a) Which of `cd`, `echo`, and `ls` is a builtin, and which lives on disk? (`type -a ls` may report an *alias* first — that is the course `.bashrc` from Lab 1 at work; the disk path is still in the list.) (b) `type -a echo` reports more than one answer — explain what that means and which one you get when you just type `echo`. The two `echo -e` commands printed the same thing; explain how you nonetheless know they were two different programs. (c) Why does `cd` *have* to be a builtin? Think about what `cd` changes and about slide 61: a disk program runs in a subshell.

---

## Part 2 — Variables and command substitution

**Q2** Run these in order, recording the output of each `echo`:

```
course=CS-265
title="Advanced Programming Tools"
echo $course
echo "I am taking $course, $title"
echo "My home is $HOME and my shell is $SHELL"
```

Now deliberately make the classic mistake:

```
course = CS-265
```

Record the message exactly. On tux it may be a bare `command not found` or a longer "did you mean…" suggestion; either way, explain what bash thought you were asking it to do.

Finally, use **command substitution** (slide 20) to produce a single line that reads like this, with the real values filled in by the shell rather than typed by you:

```
awp26 is on tux3 and today is 06 October
```

Use `$USER`, `$( hostname )`, and `$( date '+%d %B' )`. Record the command and its output.

---

## Part 3 — Quoting

The shell gets to your command line before the command does. Quoting is how you decide how much of it the shell is allowed to touch.

**Q3** Run each of these and record the output:

```
echo $USER is $USER
echo "$USER is $USER"
echo '$USER is $USER'
echo "\$USER is $USER"
echo a\\b
```

Explain, in your own words, the difference between double quotes and single quotes, and what the backslash did in the last two lines.

**Q4** Produce this exact line of output, with your own username expanded by the shell:

```
awp26 said, "I can't type $USER literally."
```

So three things must happen at once: `$USER` at the front must expand, the double quotes must appear literally, the apostrophe in `can't` must survive, and the `$USER` near the end must **not** expand. (Yes, that was four things.)

More than one answer works. Record your command and its output. Then write one sentence about why this is harder than it looks.

---

## Part 4 — Wildcards

Work in the `gallery/` directory for this question:

```
cd ~/CS265/lab2/gallery
ls
```

**Q5** Write and run a single `ls` command for each of the following. Record both the command and its output.

1. Every C source file (not the header).
2. Every file whose **second** letter is `a` (slide 15's `?a*` pattern).
3. Every `.jpeg` whose name starts with `a`, `b`, `c`, or `f`.
4. Every `.jpeg` whose name does **not** start with `a`, `c`, `d`, or `e`.
5. Every file whose name is exactly five characters long before the dot. (Hint: `?` matches exactly one character, and you may use it more than once.)

One file in `gallery/` has a space in its name. Say which of your five commands matched it, and explain why a space in a filename is a problem for the shell — then show a command that `cat`s that one file successfully. Finally, in one sentence: slide 15 says wildcards are *not* regular expressions. Given that `*` means "zero or more characters" here, what would `*` mean in a regular expression?

When you're done, `cd ..` back to `~/CS265/lab2`.

---

## Part 5 — Standard I/O

Three streams, three file descriptors: stdin is 0, stdout is 1, stderr is 2 (slide 12). They are independent, and you can aim each one separately.

**Q6 — stdout.** Run these and record what happens at each step:

```
echo first line > notes.txt
echo second line > notes.txt
cat notes.txt
echo second line >> notes.txt
cat notes.txt
```

The second command does not do what a fresh bash would do. The course `.bashrc` you installed in Lab 1 sets the `noclobber` option (slide 8). Record the message, explain what `noclobber` protects you from, then run:

```
echo overwritten anyway >| notes.txt
cat notes.txt
```

Explain what `>|` means and why `>>` never triggers the `noclobber` complaint.

**Q7 — stderr.** `ls` writes found files to stdout and complaints to stderr. Run each of these in order and record the output and the contents of any file created:

```
ls README.md nosuchfile
ls README.md nosuchfile > out.txt
cat out.txt
ls README.md nosuchfile > out.txt 2> err.txt
cat out.txt
cat err.txt
ls README.md nosuchfile > both.txt 2>&1
cat both.txt
ls README.md nosuchfile 2>&1 > oops.txt
cat oops.txt
```

Two of these need explaining. (a) Why did the error message still appear on your screen in the second command even though you redirected the output? (b) The last two look like the same thing in a different order, but they are not. Explain what `2>&1 > oops.txt` actually does and why order matters here (slide 34).

Then show the command that runs `ls README.md nosuchfile` and **discards** the error message entirely while still printing `README.md` to your screen.

**Q8 — stdin.** `<` points a command's stdin at a file instead of the keyboard (slide 35). Run:

```
sort < visits.log
```

Record just the first three lines of output. Explain the difference between `sort < visits.log` and `sort visits.log` — specifically, which one does the *shell* open the file for, and which one does `sort` open itself.

Now try a *here-string* (slide 36), which feeds one string to a command's stdin:

```
tr a-z A-Z <<< "hello from $USER"
```

Record the output.

Finally, the experience every beginner has. Run `grep tux` by itself, with no filename, and watch what happens. The shell has not frozen — slide 33 explains it. Say what the program is actually doing, then get your prompt back with Ctrl-D (press it on an empty line — if you have typed something, Ctrl-D once only flushes that text, and a second one is needed) and record what you pressed and why that works.

---

## Part 6 — Pipes

A pipe connects one process's stdout to another process's stdin (slide 37). No temp files.

**Q9** `visits.log` is a study-room door log: one username per line, one line per visit.

1. How many visits are recorded? Give a command that prints only the number.
2. How many *distinct* people visited? Give a single pipeline that prints only the number. (`sort` has a `-u` flag; `uniq` removes adjacent duplicate lines, which is why it almost always follows a `sort`.)
3. Who are the top three most frequent visitors, with their visit counts, most frequent first? Build this one stage at a time — run `sort visits.log` first, look at it, then add `| uniq -c`, look again, then add `| sort -nr`, then `| head -n 3`. Record the final pipeline and its output.

For part 3, also record what the output looked like after the `| uniq -c` stage, and explain in one sentence why `uniq` needs its input sorted first.

---

## Part 7 — Exit status, conditionals, and subshells

**Q10** Every command leaves behind an exit status in `$?`: zero means success, non-zero means failure (slide 57). Run:

```
grep -q main gallery/main.c
echo $?
grep -q zebra gallery/main.c
echo $?
```

Record both values and say which one means "found it."

Now use the conditional operators from slide 58. Run both of these and record the output:

```
cp gallery/main.c copy.c && echo "Copy succeeded"
cp no_such_file copy2.c 2> /dev/null || echo "Copy failed"
```

Explain in one sentence each what `&&` and `||` do with the exit status of the command on their left. (If you run the first line twice, `cp` will ask before overwriting `copy.c` — that is the `cp -i` alias from the course `.bashrc`, not part of this exercise.)

Last, the subshell (slides 56 and 62). Predict the output of this *before* you run it, write your prediction down, then run it:

```
drink=chocolate
( drink=strawberry ; echo "inside: $drink" ; snack=pretzel )
echo "outside: $drink"
echo "snack is: [$snack]"
```

Record your prediction, the actual output, and an explanation of why `drink` went back to `chocolate` and why `snack` is empty. Then say what you would have to add to the parentheses to make `snack` visible afterward — or explain why no addition to the parentheses can do it.

---

## Part 8 — Submit

Check that `lab2.txt` is complete — every question answered, commands pasted exactly as run.

Copy it from tux to your own machine. From a terminal **on your own machine** (not on tux), with your own username in place of `abc123`:

```
scp abc123@tux.cs.drexel.edu:CS265/lab2/lab2.txt .
```

Then upload `lab2.txt` to the Lab 2 assignment on Canvas.

**Checklist before you submit:**

- [ ] Template renamed with `mv lab2_template.txt lab2.txt`
- [ ] All ten questions answered in `lab2.txt`
- [ ] Commands pasted exactly as run, output exactly as printed
- [ ] Q4's output line matches the target exactly, with your username expanded
- [ ] Q10 includes your prediction, written before you ran the code
- [ ] `lab2.txt` uploaded to Canvas by Sunday 11:59 PM
