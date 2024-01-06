#include "puzzle.h"

void fprint_puzzle(FILE* file, puzzle_t puzzle)
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
            fprintf(file, "%u ", puzzle[row][col]);
            if (col == SSOLVE_GRID_SIZE - 1)
            {
                fprintf(file, "\n");
            }
        }
    }
}
