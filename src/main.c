#include "parse.h"
#include "puzzle.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cli_args_t
{
    bool verbose;
    const char* puzzle;
} cli_args_t;

void usage(void)
{
    printf("Solve sudoku puzzles\n");
    printf("Usage: ssolve [--help] [--verbose] <PUZZLE>\n");

    // TODO: Add --check that checks a sudoku.txt file for rule violations
}

cli_args_t parse_args(int argc, char* argv[])
{
    cli_args_t args = {0};

    struct option options[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {NULL, 0, NULL, 0},
    };

    while (true)
    {
        int option_index = 0;

        int retval = getopt_long(argc, argv, "hv", options, &option_index);
        if (retval == -1)
        {
            break;
        }

        switch (retval)
        {
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            args.verbose = true;
            break;
        case '?':
            exit(EXIT_FAILURE);
            break;
        default:
            fprintf(stderr, "Unhandled argument: '%s'\n", argv[optind - 1]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    while (optind < argc)
    {
        if (args.puzzle == NULL)
        {
            args.puzzle = argv[optind];
        }
        optind++;
    }
    if (args.puzzle == NULL)
    {
        fprintf(stderr, "Missing required positional argument <PUZZLE>\n");
    }

    return args;
}

int main(int argc, char* argv[])
{
    const cli_args_t args = parse_args(argc, argv);

    puzzle_t puzzle = {0};
    if (false == parse_puzzle(args.puzzle, puzzle))
    {
        fprintf(stderr, "Failed to parse puzzle from %s\n", args.puzzle);
        exit(EXIT_FAILURE);
    }

    // TODO: Solve the puzzle
    fprint_puzzle(stdout, puzzle);

    return 0;
}
