#include "parse.h"

#include "puzzle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool skippable_line(const char* buffer, int buf_size)
{
    for (int i = 0; i < buf_size; i++)
    {
        if (buffer[i] == '\0')
        {
            break;
        }
        // If the line contains a number, then we should parse it
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            return false;
        }
    }
    return true;
}

bool parse_line(int* row, char* buffer, int buf_size, puzzle_t puzzle)
{
    if (skippable_line(buffer, buf_size))
    {
        return true;
    }

    int col = 0;
    for (int i = 0; i < buf_size && col < SSOLVE_GRID_SIZE; i++)
    {
        if (buffer[i] == '\0')
        {
            break;
        }

        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            const uint8_t value = buffer[i] - '0';
            puzzle[*row][col++] = value;
        } else
        {
            // Skip this character
        }
    }

    if (col == SSOLVE_GRID_SIZE)
    {
        (*row)++;
        return true;
    }
    return false;
}

// The sudoku file format is a table of single-digit numbers, with non-digit numbers ignored.
// Zeros represent blanks cells.
//
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
bool parse_puzzle(const char* filename, puzzle_t puzzle)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return false;
    }

    int row = 0;

    const int buf_size = 255;
    char buffer[buf_size];
    while (row < SSOLVE_GRID_SIZE)
    {
        if (NULL == fgets(buffer, buf_size, file))
        {
            fprintf(stderr, "Parsed %d rows before EOF\n", row);
            fclose(file);
            return false;
        }

        const bool success = parse_line(&row, buffer, buf_size, puzzle);
        if (false == success)
        {
            // Buffer contains a null byte, so you can't print anything after it
            fprintf(stderr, "Failed to parse line: %s", buffer);
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}
