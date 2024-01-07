#pragma once
#include "puzzle.h"

typedef enum check_result_t
{
    SSOLVE_CHECK_UNSOLVED,
    SSOLVE_CHECK_SOLVED,
    SSOLVE_CHECK_INVALID,
} check_result_t;

check_result_t ssolve_check_puzzle(puzzle_t puzzle, puzzle_t color_hints);
