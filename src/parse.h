#pragma once
#include "puzzle.h"

#include <stdbool.h>
#include <stdint.h>

bool parse_puzzle(const char* filename, puzzle_t* puzzle);
