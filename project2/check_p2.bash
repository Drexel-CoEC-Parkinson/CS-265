#!/bin/bash
#
# check_p2.bash -- self-check for CS-265 Project 2 (logreport)
#
# Usage (from the directory that holds YOUR logreport.c):
#     bash check_p2.bash
#     bash check_p2.bash --bonus
#
# Compiles your logreport.c with the course flags and compares its
# output, error messages, and exit status against the expected files
# in tests/ (the tests/ directory next to this script). Passing every
# check here does NOT guarantee full credit: the graders also run
# tests you have not seen.

here=$(cd "$(dirname "$0")" && pwd)
tests="$here/tests"
src=logreport.c
bonus=no
[[ $1 == --bonus ]] && bonus=yes

if [[ ! -f $src ]]; then
    echo "check_p2: no $src in $(pwd) -- cd to your project2 directory first" >&2
    exit 1
fi

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
exe="$work/logreport"

pass=0
fail=0

ok()  { echo "  PASS  $1"; pass=$((pass + 1)); }
bad() { echo "  FAIL  $1"; fail=$((fail + 1)); }

# show the first few lines of a diff, indented
show_diff() {
    diff "$1" "$2" | head -n 12 | sed 's/^/          /'
    echo "          (< expected   > yours)"
}

echo "== Compiling: gcc -Wall -Wextra -g -std=c99 -o logreport $src"
if ! gcc -Wall -Wextra -g -std=c99 -o "$exe" "$src" 2> "$work/cc.txt"; then
    cat "$work/cc.txt"
    echo "  FAIL  does not compile -- nothing else can be checked"
    exit 1
fi
if [[ -s $work/cc.txt ]]; then
    cat "$work/cc.txt"
    bad "compiles, but with warnings (the graders deduct for these)"
else
    ok "compiles with no warnings"
fi

# run_test NAME LOGFILE -- compare stdout, stderr, exit status
run_test() {
    local name=$1 log=$2 base=${2%.log}
    { timeout 10 "$exe" "$log" < /dev/null > "$work/out" 2> "$work/err"; } 2> /dev/null
    local rc=$?
    if [[ $rc -eq 124 ]]; then
        bad "$name: timed out (infinite loop?)"
        return
    fi
    if cmp -s "$base.out" "$work/out"; then
        ok "$name: report"
    else
        bad "$name: report differs"
        show_diff "$base.out" "$work/out"
    fi
    if cmp -s "$base.err" "$work/err"; then
        ok "$name: malformed-line messages"
    else
        bad "$name: malformed-line messages differ"
        show_diff "$base.err" "$work/err"
    fi
    if [[ $rc -eq 0 ]]; then
        ok "$name: exit status 0"
    elif [[ $rc -eq 139 ]]; then
        bad "$name: CRASHED with a segmentation fault (bad array index" \
            "or pointer? try gdb or valgrind)"
    elif [[ $rc -gt 128 ]]; then
        bad "$name: CRASHED (killed by signal $((rc - 128)))"
    else
        bad "$name: exit status should be 0, was $rc"
    fi
}

echo
echo "== Report tests"
for t in small empty malformed ties week; do
    run_test "$t.log" "$tests/$t.log"
done

echo
echo "== Command line"
{ timeout 10 "$exe" < "$tests/small.log" > "$work/out" 2> /dev/null; } 2> /dev/null
if cmp -s "$tests/small.out" "$work/out"; then
    ok "reads standard input when no FILE is given"
else
    bad "./logreport < small.log should match small.out"
fi

{ timeout 10 "$exe" "$work/no-such-file.log" < /dev/null > "$work/out" 2> "$work/err"; } 2> /dev/null
rc=$?
if [[ $rc -eq 1 && -s $work/err && ! -s $work/out ]] &&
   grep -q "cannot open" "$work/err"; then
    ok "missing file: message on stderr, exit status 1"
else
    bad "missing file: expected 'logreport: cannot open ...' on stderr," \
        "nothing on stdout, exit status 1 (got $rc)"
fi

{ timeout 10 "$exe" a.log b.log < /dev/null > "$work/out" 2> "$work/err"; } 2> /dev/null
rc=$?
if [[ $rc -eq 2 && -s $work/err && ! -s $work/out ]]; then
    ok "two arguments: usage message on stderr, exit status 2"
else
    bad "two arguments: expected a usage message on stderr," \
        "nothing on stdout, exit status 2 (got $rc)"
fi

if [[ $bonus == yes ]]; then
    echo
    echo "== Bonus"
    run_test "bonus_big.log" "$tests/bonus_big.log"
    if command -v valgrind > /dev/null; then
        timeout 120 valgrind --leak-check=full --error-exitcode=99 \
            --log-file="$work/vg.txt" \
            "$exe" "$tests/bonus_big.log" < /dev/null > /dev/null 2>&1
        if [[ $? -eq 124 ]]; then
            bad "valgrind run timed out after 2 minutes (infinite loop?)"
        elif grep -q "ERROR SUMMARY: 0 errors" "$work/vg.txt" &&
           grep -q "All heap blocks were freed" "$work/vg.txt"; then
            ok "valgrind: no errors, all heap blocks freed"
        else
            bad "valgrind reports problems:"
            grep -E "in use at exit|definitely|indirectly|Invalid|uninitialised|ERROR SUMMARY" \
                "$work/vg.txt" | head -n 10 | sed 's/^/          /'
        fi
    else
        echo "  SKIP  valgrind is not installed here"
    fi
fi

echo
echo "== $pass passed, $fail failed"
[[ $fail -eq 0 ]]
