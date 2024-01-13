#!/bin/bash
set -o errexit

REPO_ROOT="$(git rev-parse --show-toplevel)"
git ls-files "$REPO_ROOT" |
    grep --extended-regexp '(src|include|tests)/.*\.(h|hpp|hxx|c|cc|cpp|cxx)' |
    xargs --no-run-if-empty clang-tidy --use-color --warnings-as-errors='*'
