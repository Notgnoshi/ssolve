#include "ssolve/puzzle.h"

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
bool ssolve_verbose_g = false;

void ssolve_reset(FILE* file)
{
    fprintf(file, "\033[0m");
}
void ssolve_green(FILE* file)
{
    fprintf(file, "\033[0;32m");
}
void ssolve_yellow(FILE* file)
{
    fprintf(file, "\033[0;33m");
}
void ssolve_red(FILE* file)
{
    fprintf(file, "\033[0;31m");
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void ssolve_fprint_puzzle(FILE* file,
                          ssolve_puzzle_t puzzle,  // NOLINT(bugprone-easily-swappable-parameters)
                          ssolve_puzzle_t color_hints,
                          ssolve_color_when_t when)
{
    // TODO: Minimize write(2) calls by writing to a buffer, and then finally the buffer to the file
    const bool color = when == SSOLVE_COLOR_ALWAYS;

    for (int row = 0; row < SSOLVE_GRID_SIZE; row++)
    {
        if (row != 0 && row % 3 == 0)
        {
            fprintf(file, "------+-------+------\n");
        }
        for (int col = 0; col < SSOLVE_GRID_SIZE; col++)
        {
            if (col != 0 && col % 3 == 0)
            {
                fprintf(file, "| ");
            }
            if (color && color_hints[row][col] == SSOLVE_COLOR_VALID)
            {
                ssolve_green(file);
            } else if (color && color_hints[row][col] == SSOLVE_COLOR_BLANK)
            {
                ssolve_yellow(file);
            } else if (color && color_hints[row][col] == SSOLVE_COLOR_INVALID)
            {
                ssolve_red(file);
            }
            fprintf(file, "%u", puzzle[row][col]);
            if (col != SSOLVE_GRID_SIZE - 1)
            {
                if (color_hints[row][col] != SSOLVE_COLOR_INVALID)
                {
                    fprintf(file, " ");
                }
            }
            if (color_hints[row][col] == SSOLVE_COLOR_INVALID)
            {
                fprintf(file, "<");
            }
            if (color)
            {
                ssolve_reset(file);
            }
            if (col == SSOLVE_GRID_SIZE - 1)
            {
                fprintf(file, "\n");
            }
        }
    }
}
