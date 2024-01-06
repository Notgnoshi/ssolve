#!/bin/bash
set -o errexit
set -o pipefail
set -o nounset

INPUT_FILE="$1"
if [[ ! -f "$INPUT_FILE" ]]; then
    echo "'$INPUT_FILE' does not exist" >&2
    exit 1
fi
EXPECTED_RESULTS_FILE="${INPUT_FILE%.*}.expected"
ACTUAL_RESULTS_FILE="${INPUT_FILE%.*}.actual"

./ssolve "$INPUT_FILE" >"$ACTUAL_RESULTS_FILE"

ssolve_cdiff() {
    # Use delta, if it's installed, because it give better diffs
    if command -v delta &>/dev/null; then
        delta "$@"
    else
        diff --unified --color='always' "$@"
    fi
}

ssolve_cdiff "$EXPECTED_RESULTS_FILE" "$ACTUAL_RESULTS_FILE"
