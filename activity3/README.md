# activity3/

Files for Activity 3 (Regex Golf). Instructions are in `activity3.md`.

| File | Purpose |
|---|---|
| `golf.bash` | Checker: `./golf.bash HOLE 'PATTERN'` |
| `holeN.match` | Lines your pattern must match (one per line) |
| `holeN.nomatch` | Lines your pattern must not match |

The checker uses `grep -E`. If you get `Permission denied`, run `chmod u+x golf.bash`.
