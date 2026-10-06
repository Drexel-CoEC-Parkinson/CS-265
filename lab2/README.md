# Lab 2 — The Bash Shell

Files in this directory:

| File | What it is |
| --- | --- |
| `lab2.md` | The lab handout. Read this first. |
| `lab2_template.txt` | Your answer sheet. Copy it to your working directory and fill it in. |
| `gallery/` | A folder of exported photos and a toy C program, used for the wildcard questions. |
| `visits.log` | A study-room door log: one username per visit, 40 lines. Used for the pipe questions. |

## Getting started

```
cd ~/CS265/materials
git pull
mkdir ~/CS265/lab2
cp -r lab2/* ~/CS265/lab2/
cd ~/CS265/lab2
```

The `-r` matters — `gallery/` is a directory and a plain `cp` will skip it.

Treat `~/CS265/materials` as read-only. Do your work in `~/CS265/lab2` so that
`git pull` never has anything of yours to collide with.

Submit `lab2_template.txt` to Canvas by Sunday 11:59 PM.
