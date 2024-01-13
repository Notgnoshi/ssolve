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
if [[ ! -f "$EXPECTED_RESULTS_FILE" ]]; then
    echo "'$EXPECTED_RESULTS_FILE' does not exists" >&2
    exit 1
fi
ACTUAL_RESULTS_FILE="${INPUT_FILE%.*}.actual"
CLI_ARGS_FILE="${INPUT_FILE%.*}.args"

if [[ -f "$CLI_ARGS_FILE" ]]; then
    mapfile -t <"$CLI_ARGS_FILE"
else
    echo "" | mapfile -t
fi

if ! ./ssolve --color always "${MAPFILE[@]}" "$INPUT_FILE" &>"$ACTUAL_RESULTS_FILE"; then
    # Not an error, maybe the test is expected to have a non-zero status
    echo "'ssolve' exited with non-zero status with test case '$INPUT_FILE'" >&2
fi

ssolve_cdiff() {
    # Use delta, if it's installed, because it give better diffs
    if command -v delta &>/dev/null; then
        delta "$@"
    else
        diff --unified --color='always' "$@"
    fi
}

ssolve_cdiff "$EXPECTED_RESULTS_FILE" "$ACTUAL_RESULTS_FILE"
