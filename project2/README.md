# Project 2: logreport

Read `project2.md` for the full assignment.

Quick start:

```bash
mkdir -p ~/CS265/project2
cp -r ~/CS265/materials/project2/* ~/CS265/project2/    # once only
cd ~/CS265/project2
gcc -Wall -Wextra -g -std=c99 -o logreport logreport.c
./logreport < tests/small.log      # the starter reads stdin until Part 1 is done
bash check_p2.bash                 # self-check
bash check_p2.bash --bonus         # self-check, including the malloc bonus
```

| File | Purpose |
|---|---|
| `project2.md` | Assignment handout |
| `logreport.c` | Starter file. Copy it out once, then work on your copy |
| `check_p2.bash` | Self-check. Run it from the directory that holds your `logreport.c` |
| `tests/NAME.log` | Test logs. Don't edit these |
| `tests/NAME.out` | Expected report (stdout) for each log |
| `tests/NAME.err` | Expected malformed-line messages (stderr) for each log |

Do your work in `~/CS265/project2`, not in `~/CS265/materials`. Submit only `logreport.c` on Canvas.
