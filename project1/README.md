# Project 1 — photosort

Read `project1.md` for the full assignment.

Quick start:

```bash
mkdir -p ~/CS265/project1
cp -r ~/CS265/materials/project1/* ~/CS265/project1/
cd ~/CS265/project1
bash makePhotos.bash                      # fresh test inbox in ./inbox
bash check_patterns.bash photosort        # test your six re_ patterns
./photosort -n inbox                      # dry run
```

| File | Purpose |
|---|---|
| `project1.md` | Assignment handout |
| `makePhotos.bash` | Builds `./inbox`; removes `./sorted`. Run it to reset. |
| `check_patterns.bash` | Tests the `re_` lines in your script against `tests/` |
| `tests/NAME.match` | Strings pattern NAME must match (add your own) |
| `tests/NAME.nomatch` | Strings pattern NAME must not match (add your own) |

Do your work in `~/CS265/project1`, not in `~/CS265/materials`. Submit only `photosort` on Canvas.
