#!/bin/bash
# golf.bash -- check a regex-golf pattern
# usage: ./golf.bash HOLE 'PATTERN'      e.g.  ./golf.bash 1 'txt'
hole=$1
pat=$2
if [[ $# -ne 2 || ! -f hole$hole.match ]]; then
    echo "usage: $0 HOLE 'PATTERN'   (HOLE is 1-4; quote the pattern!)" >&2
    exit 2
fi
grep -Eq -- "$pat" /dev/null; [[ $? -eq 2 ]] && { echo "grep rejected that pattern" >&2; exit 2; }
missed=$(grep -Ev -- "$pat" "hole$hole.match")
extra=$(grep -E -- "$pat" "hole$hole.nomatch")
[[ -n $missed ]] && echo "MISSED (should match):"   && sed 's/^/    /' <<< "$missed"
[[ -n $extra  ]] && echo "WRONGLY MATCHED:"         && sed 's/^/    /' <<< "$extra"
if [[ -z $missed && -z $extra ]]; then
    echo "PASS  hole $hole  length ${#pat}  pattern: $pat"
else
    echo "FAIL  keep trying"
    exit 1
fi
