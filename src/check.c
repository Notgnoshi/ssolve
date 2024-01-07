#include "check.h"

#include "puzzle.h"

// LOL. Clang-tidy complains about a congitive complexity of 65, with a threshold of 25
ssolve_check_result_t ssolve_check_puzzle(ssolve_puzzle_t puzzle, ssolve_puzzle_t color_hints)
{
    ssolve_check_result_t retval = SSOLVE_CHECK_SOLVED;

    for (int row = 0; row < SSOLVE_GRID_SIZE; row++)
    {
        for (int col = 0; col < SSOLVE_GRID_SIZE; col++)
        {
            bool found_violation = false;
            if (puzzle[row][col] == 0)
            {
                color_hints[row][col] = SSOLVE_COLOR_BLANK;
                if (retval != SSOLVE_CHECK_INVALID)
                {
                    retval = SSOLVE_CHECK_UNSOLVED;
                }
                continue;
            }

            const uint8_t self_value = puzzle[row][col];

            // Grid unit
            const int grid_row_base = row - (row % 3);
            const int grid_col_base = col - (col % 3);
            for (int grid_row = grid_row_base; grid_row < grid_row_base + 3; grid_row++)
            {
                for (int grid_col = grid_col_base; grid_col < grid_col_base + 3; grid_col++)
                {
                    // Don't check ourself against ourself
                    if (grid_row == row && grid_col == col)
                    {
                        continue;
                    }

                    const uint8_t test_value = puzzle[grid_row][grid_col];
                    if (test_value == self_value)
                    {
                        found_violation = true;
                        color_hints[grid_row][grid_col] = SSOLVE_COLOR_INVALID;
                        color_hints[row][col] = SSOLVE_COLOR_INVALID;
                        retval = SSOLVE_CHECK_INVALID;
                        if (ssolve_verbose_g)
                        {
                            fprintf(stderr,
                                    "Found violation for cell (%d, %d) [%u]: matching cell "
                                    "(%d, %d) [%u] in same grid\n",
                                    row,
                                    col,
                                    self_value,
                                    grid_row,
                                    grid_col,
                                    test_value);
                        }
                    }
                }
            }

            // Horizontal unit
            for (int test_col = 0; test_col < SSOLVE_GRID_SIZE; test_col++)
            {
                // Don't check ourself against ourself
                if (col == test_col)
                {
                    continue;
                }
                const uint8_t test_value = puzzle[row][test_col];
                if (test_value == self_value)
                {
                    found_violation = true;
                    color_hints[row][test_col] = SSOLVE_COLOR_INVALID;
                    color_hints[row][col] = SSOLVE_COLOR_INVALID;
                    retval = SSOLVE_CHECK_INVALID;
                    if (ssolve_verbose_g)
                    {
                        fprintf(stderr,
                                "Found violation for cell (%d, %d) [%u]: matching cell "
                                "(%d, %d) [%u] in same row\n",
                                row,
                                col,
                                self_value,
                                row,
                                test_col,
                                test_value);
                    }
                }
            }

            // Vertical unit
            for (int test_row = 0; test_row < SSOLVE_GRID_SIZE; test_row++)
            {
                // Don't check ourself against ourself
                if (row == test_row)
                {
                    continue;
                }
                const uint8_t test_value = puzzle[test_row][col];
                if (test_value == self_value)
                {
                    found_violation = true;
                    color_hints[test_row][col] = SSOLVE_COLOR_INVALID;
                    color_hints[row][col] = SSOLVE_COLOR_INVALID;
                    retval = SSOLVE_CHECK_INVALID;
                    if (ssolve_verbose_g)
                    {
                        fprintf(stderr,
                                "Found violation for cell (%d, %d) [%u]: matching cell "
                                "(%d, %d) [%u] in same column\n",
                                row,
                                col,
                                self_value,
                                test_row,
                                col,
                                test_value);
                    }
                }
            }

            if (found_violation == false)
            {
                color_hints[row][col] = SSOLVE_COLOR_VALID;
            }
        }
    }
    return retval;
}
