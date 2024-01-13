#include "parse.h"

#include "puzzle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool ssolve_skippable_line(const char* buffer, int buf_size)
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

bool ssolve_parse_line(int* row, char* buffer, int buf_size, ssolve_puzzle_t puzzle)
{
    if (ssolve_skippable_line(buffer, buf_size))
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
bool ssolve_parse_grid_puzzle(FILE* file, ssolve_puzzle_t puzzle)
{
    int row = 0;

    const int buf_size = 255;
    char buffer[buf_size];
    while (row < SSOLVE_GRID_SIZE)
    {
        if (NULL == fgets(buffer, buf_size, file))
        {
            fprintf(stderr, "Parsed %d rows before EOF\n", row);
            return false;
        }

        const bool success = ssolve_parse_line(&row, buffer, buf_size, puzzle);
        if (false == success)
        {
            // Buffer contains a null byte, so you can't print anything after it
            fprintf(stderr, "Failed to parse line: %s", buffer);
            return false;
        }
    }

    return true;
}

bool ssolve_line_format_valid(const char* buffer, int buf_size)
{
    int len = 0;
    for (; len < buf_size && buffer[len] != '\0'; ++len)
    {
        // Valid characters are '.' and '0'-'9'
        if (buffer[len] != '.' && (buffer[len] < '0' || buffer[len] > '9'))
        {
            return false;
        }
    }
    const int expected_len = 81;
    return len == expected_len;
}

bool ssolve_parse_line_whole(char* buffer, int buf_size, ssolve_puzzle_t puzzle)
{
    // Guarantees buffer starts with 81 valid characters
    if (ssolve_line_format_valid(buffer, buf_size) == false)
    {
        return false;
    }

    for (int row = 0, i = 0; row < SSOLVE_GRID_SIZE; ++row)
    {
        for (int col = 0; col < SSOLVE_GRID_SIZE; ++col)
        {
            if (buffer[i] >= '0' && buffer[i] <= '9')
            {
                const uint8_t value = buffer[i] - '0';
                puzzle[row][col] = value;
            } else
            {
                puzzle[row][col] = 0;
            }

            ++i;
        }
    }
    return true;
}

bool ssolve_parse_line_puzzle(FILE* file, ssolve_puzzle_t puzzle)
{
    const int buf_size = 255;
    char buffer[buf_size];
    bool success = false;

    while (success == false)
    {
        if (NULL == fgets(buffer, buf_size, file))
        {
            return false;
        }
        // Skip non-parsable lines, and stop after parsing the first puzzle
        success = ssolve_parse_line_whole(buffer, buf_size, puzzle);
        if (success)
        {
            return true;
        }
    }
    return false;
}

bool ssolve_parse_puzzle(FILE* file, ssolve_file_format_t format, ssolve_puzzle_t puzzle)
{
    switch (format)
    {
    case SSOLVE_FORMAT_GRID:
        return ssolve_parse_grid_puzzle(file, puzzle);
    case SSOLVE_FORMAT_LINE:
        return ssolve_parse_line_puzzle(file, puzzle);
    default:
        fprintf(stderr, "Unknown file format '%d'\n", format);
        exit(EXIT_FAILURE);
    }
}
