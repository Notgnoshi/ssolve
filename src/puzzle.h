#pragma once
#include <stdint.h>
#include <stdio.h>

#define SSOLVE_GRID_SIZE 9
typedef uint8_t puzzle_t[SSOLVE_GRID_SIZE][SSOLVE_GRID_SIZE];

void fprint_puzzle(FILE* file, puzzle_t puzzle);
