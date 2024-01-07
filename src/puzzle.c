#include "puzzle.h"

void ssolve_fprint_puzzle(FILE* file,
                          ssolve_puzzle_t puzzle,
                          ssolve_puzzle_t color_hints,
                          ssolve_color_when_t when)
{
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
            fprintf(file, "%u", puzzle[row][col]);
            if (col != SSOLVE_GRID_SIZE - 1)
            {
                fprintf(file, " ");
            }
            if (col == SSOLVE_GRID_SIZE - 1)
            {
                fprintf(file, "\n");
            }
        }
    }
}
