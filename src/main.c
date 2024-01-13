#include "parse.h"
#include "puzzle.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool ssolve_verbose_g = false;

typedef struct cli_args_t
{
    const char* puzzle;
} cli_args_t;

void usage(void)
{
    printf("Solve sudoku puzzles\n");
    printf("Usage: ssolve [--help] [--verbose] [PUZZLE]\n");
    printf("\n");
    printf("Positional arguments:\n");
    printf("\tPUZZLE         The puzzle file to read. If not given, defaults to stdin\n");
    printf("\n");
    printf("Options:\n");
    printf("\t--help, -h     Show this help and exit\n");
    printf("\t--verbose, -v  Increase output verbosity (on stderr)\n");

    // TODO: Add --check that checks a sudoku.txt file for rule violations
    // TODO: Add --generate?
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
            ssolve_verbose_g = true;
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

    return args;
}

int main(int argc, char* argv[])
{
    const cli_args_t args = parse_args(argc, argv);
    FILE* file = NULL;
    if (args.puzzle == NULL || (args.puzzle[0] == '-' && args.puzzle[1] == '\0'))
    {
        file = stdin;
    } else
    {
        file = fopen(args.puzzle, "r");
        if (file == NULL)
        {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
    }

    puzzle_t puzzle = {0};
    if (false == parse_puzzle(file, puzzle))
    {
        fprintf(stderr, "Failed to parse puzzle from %s\n", args.puzzle);
        exit(EXIT_FAILURE);
    }

    if (ssolve_verbose_g)
    {
        fprintf(stderr, "Parsed puzzle:\n");
        fprint_puzzle(stderr, puzzle);
    }

    // TODO: Solve the puzzle

    // Finally, print the solved puzzle
    fprint_puzzle(stdout, puzzle);

    return 0;
}
