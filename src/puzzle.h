#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

extern bool ssolve_verbose_g;

#define SSOLVE_GRID_SIZE 9

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
typedef uint8_t puzzle_t[SSOLVE_GRID_SIZE][SSOLVE_GRID_SIZE];

typedef enum color_when_t
{
    SSOLVE_COLOR_AUTO,  // Default
    SSOLVE_COLOR_NEVER,
    SSOLVE_COLOR_ALWAYS,
} color_when_t;

typedef enum color_hint_t
{
    SSOLVE_COLOR_NONE,     // no color
    SSOLVE_COLOR_VALID,    // green
    SSOLVE_COLOR_BLANK,    // yellow
    SSOLVE_COLOR_INVALID,  // red
} color_hint_t;
void fprint_puzzle(FILE* file, puzzle_t puzzle, puzzle_t color_hints, color_when_t when);
