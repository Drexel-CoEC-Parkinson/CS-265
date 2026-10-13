#!/bin/bash
# check_patterns.bash -- test the six re_ patterns in your photosort
#
# Usage:  bash check_patterns.bash photosort [name]
#         name is one of: android pixel screenshot whatsapp date time
#
# Reads ONLY the re_NAME='...' lines from your script (it never runs your
# script), then tests each pattern with [[ =~ ]] -- the same matcher your
# script uses -- against tests/NAME.match (every line must match) and
# tests/NAME.nomatch (no line may match).

names="android pixel screenshot whatsapp date time"

if (( $# < 1 || $# > 2 )) ; then
    echo "usage: bash check_patterns.bash photosort [name]" >&2
    exit 1
fi

script=$1
only=$2

if [[ ! -f $script || ! -r $script ]] ; then
    echo "check_patterns: cannot read '$script'" >&2
    exit 1
fi

if [[ -n $only && " $names " != *" $only "* ]] ; then
    echo "check_patterns: unknown pattern '$only' (choose from: $names)" >&2
    exit 1
fi

testdir=${0%/*}/tests
[[ $0 == */* ]] || testdir=tests

total_fail=0

# check_one name
check_one() {
    local name=$1
    local line count value pass=0 fail=0 status

    # Find the assignment line
    count=$(grep -c "^re_$name=" "$script")
    if (( count == 0 )) ; then
        echo "$name: MISSING -- no line starting with re_$name= in $script"
        (( total_fail++ ))
        return
    fi
    if (( count > 1 )) ; then
        echo "$name: ERROR -- re_$name= is assigned $count times; keep exactly one"
        (( total_fail++ ))
        return
    fi
    line=$(grep "^re_$name=" "$script")

    # Must be exactly re_name='pattern' (single quotes; a trailing # comment is OK)
    if [[ ! $line =~ ^re_$name=\'([^\']*)\'[[:space:]]*(#.*)?$ ]] ; then
        echo "$name: FORMAT -- expected re_$name='...' on one line, got:"
        echo "    $line"
        (( total_fail++ ))
        return
    fi
    value=${BASH_REMATCH[1]}

    if [[ -z $value ]] ; then
        echo "$name: EMPTY -- the pattern is blank"
        (( total_fail++ ))
        return
    fi

    # Is it a valid ERE? (status 2 from =~ means the regex didn't compile)
    [[ x =~ $value ]]
    if (( $? == 2 )) ; then
        echo "$name: INVALID -- bash can't compile this regex: $value"
        (( total_fail++ ))
        return
    fi

    # \d \w \s are Perl-style shortcuts that bash's =~ does not support
    if [[ $value == *'\d'* || $value == *'\w'* || $value == *'\s'* ]] ; then
        echo "  NOTE $name: \\d, \\w and \\s don't work in bash's =~; use [0-9], [[:digit:]], etc."
    fi

    # Strings that must match
    while IFS= read -r line ; do
        [[ -z $line || $line == \#* ]] && continue
        if [[ $line =~ $value ]] ; then
            (( pass++ ))
        else
            (( fail++ ))
            echo "  FAIL $name: should match:     $line"
        fi
    done < "$testdir/$name.match"

    # Strings that must not match
    while IFS= read -r line ; do
        [[ -z $line || $line == \#* ]] && continue
        if [[ $line =~ $value ]] ; then
            (( fail++ ))
            echo "  FAIL $name: should NOT match: $line"
        else
            (( pass++ ))
        fi
    done < "$testdir/$name.nomatch"

    if (( fail == 0 )) ; then
        status=PASS
    else
        status=FAIL
        (( total_fail++ ))
    fi
    echo "$name: $status ($pass/$(( pass + fail )) tests)"
}

for n in $names ; do
    [[ -n $only && $n != "$only" ]] && continue
    if [[ ! -r $testdir/$n.match || ! -r $testdir/$n.nomatch ]] ; then
        echo "check_patterns: missing $testdir/$n.match or $n.nomatch" >&2
        exit 1
    fi
    check_one "$n"
done

if (( total_fail == 0 )) ; then
    echo "All checked patterns pass the provided tests."
    echo "(Grading also uses hidden tests -- add your own lines to tests/.)"
fi
(( total_fail == 0 ))
