# Lab 3: Regular Expressions, with a Side of sed and AWK

**CS-265: Advanced Programming Tools & Techniques** · 10 questions · 100 points · Due **Sunday 11:59 PM**

## Setup

```bash
cd ~/CS-265 && git pull
cp -r lab3 ~/lab3 && cd ~/lab3
cp lab3_template.txt lab3.txt
```

Answer in `lab3.txt`. For each question, paste the **exact command** you ran and its **output**, plus any explanation asked for.

Use `grep -E` throughout. All questions except Q3 and Q4 use `directory.csv`, a fake department directory. Look at it first (`cat directory.csv`). It has comment lines, blank lines, and some messy entries on purpose.

Columns: `name,title,email,phone,room,start`

> **Quote every pattern** with single quotes. Unquoted `|`, `*`, `$`, `(`, and `?` belong to the shell before grep ever sees them.

---

## Q1. Escaping the dot (10 pts)

Run both commands and record the counts:

```bash
grep -c 'Dr.'  directory.csv
grep -c 'Dr\.' directory.csv
```

The counts differ by one. Find the extra line the first command matched, and explain why it matched.

## Q2. Anchors: skipping comments and blanks (10 pts)

Write **one** `grep` that prints only the people: no comment lines (lines starting with `#`) and no blank lines. Pipe it to `wc -l`.

Then explain in one sentence what `^$` matches.

## Q3. Word anchors (10 pts)

Use `memo.txt`. **Before running anything**, predict which of these gives the bigger number, and why:

```bash
grep -o 'is'     memo.txt | wc -l
grep -o '\<is\>' memo.txt | wc -l
```

Run both and record the counts. List three different words that the first pattern matched inside but the second didn't.

Then add `-i` to the second command. Why does the count go up by exactly one?

## Q4. Greed (10 pts)

Use `tags.html`.

1. Predict the output of `grep -o '<.*>' tags.html`, then run it. Explain the result in terms of greediness.
2. Fix it with an inverted character class so each tag prints on its own line.
3. Write a pattern that prints just the two bold elements: `<b>Tuesday</b>` and `<b>Thursday</b>`.

## Q5. Character classes: standard phone numbers (10 pts)

A standard phone number here looks like `215-895-0142`: three digits, dash, three digits, dash, four digits.

Using your Q2 command as the first stage of a pipeline, print the **names** (only the names) of people whose phone field is *not* in standard form. Use `cut` to get the names.

*Hint:* anchor your pattern between the commas around the phone field.

## Q6. Drexel email addresses (10 pts)

A valid Drexel address here is lowercase letters, optional digits, then exactly `@drexel.edu`. Someone tried:

```bash
grep -oE '\<[a-z]+[0-9]*@drexel\.edu\>' directory.csv
```

It prints 9 addresses, but only 8 are real.

1. Which one is fake, and why did `\>` let it through?
2. Fix the pattern so exactly 8 addresses print, with no commas in the output.
3. Explain why `FA2006@drexel.edu` is (correctly) not in either list.

## Q7. Alternation and grouping (10 pts)

Print the names of everyone whose start date is in **2018 through 2022**, inclusive.

Use a group with `|`, for example `20(…|…)`, rather than listing five years. Your pattern must be anchored to the start-date field, so a phone number or room containing `2019` can't fool it.

## Q8. Optional pieces with `?` (10 pts)

The 215-895 phone numbers come in three styles:

```
215-895-0142
215.895.1912
(215) 895-0002
```

1. Write **one** pattern that matches all three styles, using `?` and escaped parentheses. Report `grep -c` for your pattern.
2. Then use `-v` to show the single person in the file with no 215-895 number at all. Combine it with your Q2 pattern so no comment or blank lines appear.

## Q9. sed: reformatting dates (10 pts)

Using **one** `sed` command, print the directory with:

- comment and blank lines deleted, and
- every start date changed from `YYYY-MM-DD` to `MM/DD/YYYY`.

Use `\( \)` and `\1 \2 \3` backreferences. Pick a delimiter other than `/` so your slashes don't need escaping. Show the output piped through `head -3`. The first line should be:

```
Ada Byron,Prof.,ab42@drexel.edu,215-895-0142,1139,09/03/2019
```

After running it, `directory.csv` itself is unchanged. Which `sed` option would change that, and why don't you want it here?

## Q10. AWK: people per room (10 pts)

Write a one-line `awk` program (using `-F,`) that counts how many people are in each **numbered** room:

- Only count records whose room field matches a regex for "all digits."
- Print each room and its count in an `END` block.
- Pipe the output through `sort`.

Then answer: two people are excluded by your room regex. Who are they, and why?

---

## Submitting

1. Copy your answers back to your own computer (see the scp guide), for example:

   ```bash
   scp <you>@tux.cs.drexel.edu:lab3/lab3.txt .
   ```

2. Upload `lab3.txt` to the **Lab 3** assignment on Canvas.

Late policy: −10 / −20 / −30 per day; not accepted after 4 days.
