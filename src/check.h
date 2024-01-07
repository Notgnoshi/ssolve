#pragma once
#include "puzzle.h"

typedef enum ssolve_check_result_t
{
    SSOLVE_CHECK_UNSOLVED,
    SSOLVE_CHECK_SOLVED,
    SSOLVE_CHECK_INVALID,
} ssolve_check_result_t;

ssolve_check_result_t ssolve_check_puzzle(ssolve_puzzle_t puzzle, ssolve_puzzle_t color_hints);
