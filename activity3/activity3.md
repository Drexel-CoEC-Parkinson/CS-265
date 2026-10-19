# Activity 3: Regex Golf

**CS-265: Advanced Programming Tools & Techniques** · In-class activity · 15 minutes · 5 points (effort)

Groups are fine; everyone submits their own answers on Canvas (text entry) by **11:59 PM today**.

## Setup (1 min)

```bash
cd ~/CS-265 && git pull
cd activity3
mkdir ~/CS265/activity3
cp -r activity3/* ~/CS265/activity3/
cd ~/CS265/activity3
```

Each *hole* has two files:

- `holeN.match`: every line must match your pattern
- `holeN.nomatch`: no line may match your pattern

The checker tells you what you missed or wrongly matched:

```bash
./golf.bash 1 'txt'
```

**Always single-quote your pattern** so the shell keeps its hands off `|`, `*`, `$`, and friends. A pass prints the pattern's length. In golf, shorter is better, but a working pattern beats a short broken one.

## Hole 1: File extensions

Match file names ending in `.txt` or `.log`.

| Match | Don't match |
|---|---|
| `notes.txt` `lab3.txt` `server.log` `access.log` `my.notes.txt` | `notes.text` `catalog` `dialog` `lab3_txt` `notes.txt.bak` `txt.md` |

## Hole 2: Drexel-style user IDs

Lowercase letters followed by digits, and nothing else.

| Match | Don't match |
|---|---|
| `awp26` `kss35` `sa3824` `jam993` `bm4` | `Awp26` `awp` `26awp` `aw p26` `kss35x` `x9y9` |

## Hole 3: The word "the"

Match lines containing *the* as a whole word.

| Match | Don't match |
|---|---|
| `in the box` · `the end` · `lift the latch` · `end of the` · `is the-best` | `there it is` · `bathe daily` · `another day` · `theme park` · `THE END` |

## Hole 4 (back nine, if you have time): 24-hour clock times

Times from `00:00` to `23:59`.

| Match | Don't match |
|---|---|
| `00:00` `09:45` `13:07` `19:59` `20:00` `23:59` | `24:00` `9:45` `12:60` `23:5` `123:45` `29:00` `1300` |

## Submit on Canvas

1. Your passing pattern for Holes 1–3, with the length the checker printed. Add Hole 4 if you got it.
2. For Hole 1, `.(txt|log)$` matches `catalog`. In one sentence, explain why.
3. Someone in your group tries `\d` for "a digit" in Hole 2 and it fails. Try it. What does `[0-9]` do that `\d` doesn't, in `grep -E`?
