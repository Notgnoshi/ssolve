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

case "$INPUT_FILE" in
*/check-*)
    # Include color in the output, because it lets us test the validity checking in more detail
    if ! ./ssolve --color always --check "$INPUT_FILE" &>"$ACTUAL_RESULTS_FILE"; then
        echo "'solve --check $INPUT_FILE' exited with non-zero status" >&2
    fi
    ;;
*)
    if ! ./ssolve --color never "$INPUT_FILE" &>"$ACTUAL_RESULTS_FILE"; then
        echo "'ssolve $INPUT_FILE' exited with non-zero status" >&2
    fi
    ;;
esac

ssolve_cdiff() {
    # Use delta, if it's installed, because it give better diffs
    if command -v delta &>/dev/null; then
        delta "$@"
    else
        diff --unified --color='always' "$@"
    fi
}

ssolve_cdiff "$EXPECTED_RESULTS_FILE" "$ACTUAL_RESULTS_FILE"
