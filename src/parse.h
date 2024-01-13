#pragma once
#include "puzzle.h"

#include <stdbool.h>
#include <stdio.h>

// The grid file format is a table of single-digit numbers, with non-digit numbers ignored.
// Zeros or periods represent blanks cells.
//
//     0 1 2 | 3 4 5 | 6 7 8
//     1 0 0 | 0 0 0 | 0 0 0
//     2 0 0 | 0 0 0 | 0 0 0
//     ------+-------+------
//     3 0 0 | 0 0 0 | 0 0 0
//     4 0 0 | 0 0 0 | 0 0 0
//     5 0 0 | 0 0 0 | 0 0 0
//     ------+-------+------
//     6 0 0 | 0 0 0 | 0 0 0
//     7 0 0 | 0 0 0 | 0 0 0
//     8 0 0 | 0 0 0 | 0 0 0
//
// The line file format is a single line of 81 characters. Zeros or periods represent blank cells.
//
//    .5..83.17...1..4..3.4..56.8....3...9.9.8245....6....7...9....5...729..861.36.72.4
typedef enum ssolve_file_format_t
{
    SSOLVE_FORMAT_GRID,
    SSOLVE_FORMAT_LINE,
} ssolve_file_format_t;

// Parses until success, returning 'true' after the first success, or false if it hit the end of the
// file.
//
// NOTE: A disadvantage of skipping lines that fail to parse is suppression of parser errors.
bool ssolve_parse_puzzle(FILE* file, ssolve_file_format_t format, ssolve_puzzle_t puzzle);
