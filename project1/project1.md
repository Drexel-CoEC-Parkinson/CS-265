# CS-265: Advanced Programming Tools & Techniques
## Project 1 — `photosort`: Organizing a Photo Dump with Bash and Regular Expressions

**Released:** Tuesday, October 13, 2026
**Due:** Sunday, November 8, 2026, 11:59 PM (submitted on Canvas)
**Points:** 100 (15% of course grade)
**Late policy:** −10 / −20 / −30 points per day late; not accepted after 4 days.

---

### The Scenario

You've just copied a semester's worth of photos off your phone, your friend's phone, and a group chat into one folder. Every device names its files differently:

| Source         | Example filename                     |     |
| -------------- | ------------------------------------ | --- |
| Android camera | `IMG_20260914_153012.jpg`            |     |
| Google Pixel   | `PXL_20260914_153012345.jpg`         |     |
| Screenshot     | `Screenshot_2026-09-14-15-30-12.png` |     |
| WhatsApp       | `IMG-20260914-WA0007.jpg`            |     |
| iPhone         | `IMG_1234.HEIC`                      |     |
| Digital camera | `DSC01234.JPG`                       |     |

Some files were downloaded twice and picked up suffixes like `IMG_20260914_153012(1).jpg` or `IMG_20260914_153012 (1).jpg`. A few have spaces in their names, and a few have dates that can't be real. There are also iPhone `.AAE` sidecar files, which aren't photos at all.

You'll write **`photosort`**, a single Bash script that sorts this mess into a dated folder tree:

```
sorted/
├── 2026/
│   ├── 09/
│   │   ├── 2026-09-14_153012.jpg
│   │   └── 2026-09-14_153012-1.jpg
│   └── 10/
│       └── 2026-10-02_000000.jpg
└── unsorted/
    ├── IMG_1234.HEIC
    └── DSC01234.JPG
```

The files you'll work with are empty placeholders. Only their **names** matter; your script never opens a file.

---

### Getting Started

```bash
cd ~/CS265/materials && git pull
mkdir -p ~/CS265/project1
cp -r ~/CS265/materials/project1/* ~/CS265/project1/
cd ~/CS265/project1
bash makePhotos.bash          # builds a fresh test inbox in ./inbox
```

Run `bash makePhotos.bash` any time you want to reset. It rebuilds `inbox/` and removes `sorted/`.

Provided files:

| File | Purpose |
|---|---|
| `project1.md` | This handout |
| `makePhotos.bash` | Generates the test inbox |
| `check_patterns.bash` | Tests the regex patterns in your `photosort` |
| `tests/` | `*.match` and `*.nomatch` test lists for each pattern |

---

### Part 1 — The Patterns (24 points)

The first lines of `photosort` after the header comment must define six extended regular expressions (EREs), exactly like this, with your patterns filled in:

```bash
#!/bin/bash
# (header comment)

# ---- Patterns ----
re_android='...'
re_pixel='...'
re_screenshot='...'
re_whatsapp='...'
re_date='...'
re_time='...'
# ------------------
```

Format requirements:
- One assignment per line, starting at the beginning of the line, with no spaces around "=".
- Each pattern in **single quotes**, so the shell leaves backslashes and `$` alone.
- Exactly these six variable names. The script testing your function will be looking for these variables buy name.

Each pattern matches a **base name**: the filename with its extension and any duplicate suffix already removed. For example, `IMG_20260914_153012(1).jpg` has the base name `IMG_20260914_153012`.

| Variable        | Must match exactly                                                 | Example                          |
| --------------- | ------------------------------------------------------------------ | -------------------------------- |
| `re_android`    | `IMG_`, 8 digits, `_`, 6 digits                                    | `IMG_20260914_153012`            |
| `re_pixel`      | `PXL_`, 8 digits, `_`, 9 digits                                    | `PXL_20260914_153012345`         |
| `re_screenshot` | `Screenshot_` then `YYYY-MM-DD-HH-MM-SS` (all digits)              | `Screenshot_2026-09-14-15-30-12` |
| `re_whatsapp`   | `IMG-`, 8 digits, `-WA`, 4 digits                                  | `IMG-20260914-WA0007`            |
| `re_date`       | An 8-digit date `YYYYMMDD`: year 2000–2099, month 01–12, day 01–31 | `20260914` ✓, `20261399` ✗       |
| `re_time`       | A 6-digit time `HHMMSS`: hour 00–23, minute 00–59, second 00–59    | `153012` ✓, `246000` ✗           |

**Rules:**
- **Anchor every pattern with `^` and `$`.** `[[ =~ ]]` succeeds if the pattern matches *anywhere* in the string, so an unanchored pattern will fail the `nomatch` tests.
- **Don't use `\d`, `\w`, or `\s`.** Those shortcuts (slide 21) work in some tools but not in Bash's "=~", where they silently fail to match. Use `[0-9]` or `[[:digit:]]` instead.
- `re_date` doesn't need to know that February has 28 days. `20260231` may pass.
- You may use the ERE interval `{n}`, as in `[0-9]{8}`. It isn't in the slides; see `man 7 regex`, which slide 28 points to. Writing out `[0-9][0-9]…` works too.
- Watch for near-misses. `IMG_1234` (iPhone) must **not** match `re_android`, and `IMG_20260914_153012` must **not** match `re_whatsapp`.

Test your patterns at any point, even before the rest of the script exists:

```bash
bash check_patterns.bash photosort            # all six
bash check_patterns.bash photosort android    # just one
```

The checker reads only the six `re_` lines from your file and tests them. It does not run your script.

Each pattern is worth 4 points. Grading uses the provided tests **plus additional hidden tests**, so passing the provided tests is necessary but not sufficient. Add your own lines to the files in `tests/`.

> **Real-world note:** Keeping fixed patterns as constants at the top of a script is standard practice for small tools. Larger tools often move patterns like these into separate configuration files, so they can be changed without editing code. Examples include `grep -f` word lists, log-monitoring rules, and spam filters. Either way, testing patterns separately from the code that uses them is good practice, and that's what `check_patterns.bash` does.

---

### Part 2 — The Script (64 points)

#### Usage

```
photosort [-n] [-v] [-d dest] inbox
```

| Option | Meaning |
|---|---|
| `-n` | Dry run. Print what *would* happen; create and move nothing. |
| `-v` | Verbose. Print one line per file moved or skipped. |
| `-d dest` | Destination directory. Default: `sorted` (relative to the current directory). |
| `inbox` | Required. The directory containing the files to sort. |

`-n` implies `-v`, so a dry run always prints its plan.

#### Processing each file

Process every entry directly inside `inbox`, without recursing into subdirectories. For each entry:

1. **Skip silently** anything that is not a regular file, and any hidden file (name starts with `.`).
2. **Split** the name into a base and an extension at the *last* dot. A name with no dot is **skipped**.
3. **Lowercase** the extension. If it is not one of `jpg jpeg png heic mp4 mov`, the file is **skipped** and left in the inbox. Normalize `jpeg` to `jpg`.
4. **Strip a duplicate suffix** from the base: a trailing `(N)` or ` (N)`, where N is one or more digits.
5. **Classify** the base using your patterns, in this order: android, pixel, screenshot, whatsapp. If none match, the file is **unsorted**.
6. **Extract** the date and time:

   | Scheme | Date | Time |
   |---|---|---|
   | android | the 8 digits | the 6 digits |
   | pixel | the 8 digits | the first 6 of the 9 digits (drop milliseconds) |
   | screenshot | `YYYY` `MM` `DD` fields | `HH` `MM` `SS` fields |
   | whatsapp | the 8 digits | `000000` (unknown) |

7. **Validate** the date with `re_date` and the time with `re_time`. If either fails, the file is **unsorted**. Count it under `unsorted`, not under its scheme.
8. **Build the target path:**
   - Dated: `dest/YYYY/MM/YYYY-MM-DD_HHMMSS.ext`, using the lowercased, normalized extension.
   - Unsorted: `dest/unsorted/<original filename, unchanged>`.
9. **Avoid collisions.** If the target already exists, insert `-1` before the extension. If that also exists, try `-2`, and so on. Examples: `2026-09-14_153012-1.jpg`, `IMG_1234-1.HEIC`. **Never overwrite a file.** When several inbox files map to the same name, which one gets the plain name and which get `-1`, `-2` depends on the order the glob lists them; any order is fine.
10. **Create directories** as needed (`mkdir -p`) and `mv` the file. If `mv` or `mkdir` fails, print an error to stderr and continue with the next file.

#### Output format (exact; this is autograded)

With `-v` or `-n`, print one line for each move:

```
'IMG_20260914_153012(1).jpg' -> 'sorted/2026/09/2026-09-14_153012-1.jpg'
```

In dry-run mode, prefix each move line with `(dry run) `:

```
(dry run) 'IMG_1234.HEIC' -> 'sorted/unsorted/IMG_1234.HEIC'
```

With `-v` or `-n`, print one line for each skipped file:

```
skip: 'IMG_1234.AAE'
```

After all files, **always** print a summary to stdout, in exactly this order:

```
Summary
android: 7
pixel: 4
screenshot: 4
whatsapp: 4
unsorted: 15
skipped: 5
collisions: 5
```

The numbers above are what a correct script prints for the inbox that `makePhotos.bash` builds. `collisions` counts the files that needed a `-N` suffix.

**Dry-run collisions:** a dry run checks collisions only against files that *already exist* in `dest`. It does not need to predict collisions between files in the same batch, so a dry run's plan may differ from a real run. (A dry run on a fresh inbox reports `collisions: 0`.) That's expected.

#### Errors and exit status

| Situation | Behavior | Exit status |
|---|---|---|
| Successful run (including a dry run) | — | 0 |
| No `inbox` argument, or an unknown option | Print a usage message to **stderr** | 1 |
| `inbox` doesn't exist or isn't a directory | Print `photosort: 'X' is not a directory` to stderr | 1 |
| `dest` exists but isn't a directory | Print `photosort: 'X' is not a directory` to stderr | 1 |
| One or more files failed to move | Print an error per file to stderr; finish the run | 2 |

#### Required techniques

Your script must:
- Start with `#!/bin/bash` and run as `./photosort` (execute bit set).
- Parse options with `getopts`.
- Define and use **at least three functions** (e.g., `usage`, `classify`, `unique_target`), using `local` for function-internal variables.
- Use a `case` statement somewhere meaningful (the extension check is a natural fit).
- Classify and validate with **your `re_` patterns**, using `[[ $base =~ $re_android ]]` and so on.
- Split names and extract fields with **parameter expansion** (`${f%.*}`, `${f##*.}`, `${ext,,}`, `${base:4:8}`, …).
- Use `(( ))` for counters and arithmetic.
- Handle filenames containing spaces correctly.

Your script must **not**:
- Use `sed`, `awk`, `perl`, `python`, `find`, `cut`, or `basename`. Parameter expansion does all of this.
- Parse the output of `ls`.
- Modify, rename, or delete anything except by moving files out of the inbox.

#### Hints

- **One exception to "always quote variables":** the regex on the right of `=~` must stay unquoted. `[[ $base =~ "$re_android" ]]` treats the pattern as a literal string, so it will almost never match. Try both at the prompt and check `$?`.
- `for f in $(ls inbox)` breaks on names with spaces (slide 31). Loop over a glob instead: `for f in "$inbox"/* ; do`.
- A glob that matches nothing stays as the literal string `inbox/*`. Guard against it with `[[ -e $f ]] || continue`.
- `bash -x ./photosort -n inbox` shows every expansion as it happens. It's the fastest way to see why a file landed where it did.

---

### Style and Robustness (12 points)

- A header comment with your name, Drexel ID, date, and a one-line description.
- `bash -n photosort` reports nothing.
- Variables quoted wherever word splitting or globbing could bite (with the `=~` exception above).
- Consistent indentation and meaningful names for functions and variables.
- An empty inbox prints the summary with all zeros and exits 0.

---

### Structure Tips

- **Order matters.** Bash runs top to bottom, and functions must be defined before they’re called. A sensible layout is:
    1. Header and patterns
    2. Defaults and counters
    3. Functions
    4. Option parsing
    5. Argument checks
    6. The main loop
    7. Summary and exit
- **Use small functions.** Good candidates are printing usage, classifying a name, and finding a non-colliding target. If your main loop runs longer than a screen, move a step into a function.
- **Functions can’t return strings.** `return` only sets an exit status. Instead, set a global variable, or `echo` the result and capture it with `$( )`. Remember that `$( )` runs in a subshell, so any counters it changes are lost. Use `local` for variables that are only needed inside a function.
- **Build in layers.**
    1. Print what you’d do before you move anything. That early version becomes your `-n` mode.
    2. Add moving and collisions.
    3. Add options and error handling last.
- **Reset often.** Run `bash makePhotos.bash` after every real run. On that inbox, a correct script prints 7 / 4 / 4 / 4 / 15 / 5 / 5 in the summary.
- Test each piece at the prompt before putting it into the script.

---

### Grading Summary

| Component | Points |
|---|---|
| Part 1: six patterns (4 each, provided + hidden tests) | 24 |
| Part 2: `photosort` run against a hidden test inbox | 64 |
| Style and robustness | 12 |
| **Total** | **100** |

Part 2 breakdown:

| Area | Points |
|---|---|
| Classification and date extraction | 18 |
| Target paths and extension normalization | 12 |
| `-n`, `-v`, `-d` options | 10 |
| Collisions | 8 |
| Summary counts | 6 |
| Errors and exit codes | 6 |
| Spaces and duplicate suffixes | 4 |

---

### Submission

Copy `photosort` to your own machine with `scp` as in previous labs this term, then upload it to the **Project 1** assignment on Canvas. That one file is your entire submission.

## Your script will be graded on tux, so make sure it runs there and not just on your laptop.
