# CS-265: Advanced Programming Tools & Techniques

Course materials for CS-265 at Drexel University (Fall 2026): handouts, starter files, and configuration for the in-class activities and labs. This repository is **read-only for students**; you can't push to it, and you shouldn't need to.

## Getting a copy

Do this once, on tux, during Lab 1:

```
mkdir ~/CS265
chmod 700 ~/CS265
git clone https://github.com/Drexel-CoEC-Parkinson/CS-265 ~/CS265/materials
```

No GitHub account or password is needed.

## Keeping it current

New material is pushed the day it's released. Before every class:

```
cd ~/CS265/materials && git pull
```

If `git pull` prints `Already up to date.`, you're current. If it prints anything about *conflicts* or *local changes*, you edited something inside `materials/` — see the rules below, then ask for help.

## Two rules

1. **Never work inside `~/CS265/materials`.** Copy what you need *out* to your own directory for that lab, e.g.

   ```
   mkdir ~/CS265/lab2
   cd ~/CS265/lab2
   cp ~/CS265/materials/lab2/* .
   ```

   Editing files inside `materials/` will break `git pull` for you later.

2. **Submit on Canvas, not here.** Nothing you put in this repo, or in your clone of it, is seen or graded. Every lab and activity tells you exactly which files to `scp` down and upload.

## Layout

```
README.md          this file
dotfiles/          bashrc, inputrc, vimrc  — installed as ~/.bashrc etc. in Lab 1
activity1/ … 8/    in-class activities (activityN.md plus any data files)
lab1/ … 8/         labs (labN.md, labN_template.txt, starter files, README.md)
```

Directory numbers match the Canvas assignment numbers, not calendar weeks. Directories for labs that haven't been released yet won't appear until they are.

## Something's wrong

- **`git pull` fails** — you probably edited a file inside `materials/`. Quickest fix: `cd ~/CS265 && rm -rf materials` and clone again. You lose nothing, because your work isn't in there (rule 1).
- **A file mentioned in a handout isn't in the directory** — run `git pull` first. If it's still missing, tell us in class.
- **Tux itself** (can't log in, password problems) — that's the CCI help desk, `ihelp@drexel.edu`.

## Instructors

Drew Parkinson (`awp26@drexel.edu`). Office hours and TA hours are on the Canvas syllabus.
