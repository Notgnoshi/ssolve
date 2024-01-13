#!/bin/bash
set -o errexit
set -o pipefail
set -o nounset
set -o noclobber

## Extract a single puzzle from the given file of puzzles

PUZZLE_FILE="$1"
PUZZLE_INDEX="${2:-0}"

if [[ ! -f "$PUZZLE_FILE" ]]; then
    echo "'$PUZZLE_FILE' does not exist" >&2
    exit 1
fi

# Each puzzle is 9 lines line, separated by a blank line
PUZZLE_SIZE=10

START_LINE=$((PUZZLE_SIZE * PUZZLE_INDEX))
END_LINE=$((START_LINE + PUZZLE_SIZE))

# shellcheck disable=SC2002
cat "$PUZZLE_FILE" |
    head --lines $END_LINE |
    tail --lines $PUZZLE_SIZE
