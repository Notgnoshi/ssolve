#pragma once
#include "puzzle.h"

#include <stdbool.h>
#include <stdio.h>

typedef enum ssolve_file_format_t
{
    SSOLVE_FORMAT_GRID,
    SSOLVE_FORMAT_LINE,
} ssolve_file_format_t;
bool ssolve_parse_puzzle(FILE* file, ssolve_file_format_t format, ssolve_puzzle_t puzzle);
