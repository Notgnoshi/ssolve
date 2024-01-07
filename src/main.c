#include "check.h"
#include "parse.h"
#include "puzzle.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool ssolve_verbose_g = false;

typedef enum operation_t
{
    SSOLVE_OP_SOLVE = 0,  // default
    SSOLVE_OP_CHECK,
} operation_t;

typedef struct cli_args_t
{
    operation_t op;
    color_when_t color;
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
    printf("\t--check, -c    Instead of solving, check the validity of the given puzzle\n");
    printf("\t--color, -C    When to color the output. 'never', 'auto', or 'always'\n");

    // TODO: Add --generate?
}

cli_args_t parse_args(int argc, char* argv[])
{
    cli_args_t args = {0};

    struct option options[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"check", no_argument, NULL, 'c'},
        {"color", required_argument, NULL, 'C'},
        {NULL, 0, NULL, 0},
    };

    while (true)
    {
        int option_index = 0;

        int retval = getopt_long(argc, argv, "hvcC:", options, &option_index);
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
        case 'c':
            args.op = SSOLVE_OP_CHECK;
            break;
        case 'C':
            if (strcmp(optarg, "never") == 0)
            {
                args.color = SSOLVE_COLOR_NEVER;
            } else if (strcmp(optarg, "auto") == 0)
            {
                args.color = SSOLVE_COLOR_AUTO;
            } else if (strcmp(optarg, "always") == 0)
            {
                args.color = SSOLVE_COLOR_ALWAYS;
            } else
            {
                fprintf(stderr, "Unknown argument to --color: '%s'\n", optarg);
                exit(EXIT_FAILURE);
            }
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

    if (args.color == SSOLVE_COLOR_AUTO)
    {
        if (isatty(1))
        {
            args.color = SSOLVE_COLOR_ALWAYS;
        } else
        {
            args.color = SSOLVE_COLOR_NEVER;
        }
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
    puzzle_t color_hints = {0};
    if (false == parse_puzzle(file, puzzle))
    {
        fprintf(stderr, "Failed to parse puzzle from %s\n", args.puzzle);
        exit(EXIT_FAILURE);
    }

    if (ssolve_verbose_g)
    {
        fprintf(stderr, "Parsed puzzle:\n");
        fprint_puzzle(stderr, puzzle, color_hints, args.color);
    }

    switch (args.op)
    {
    case SSOLVE_OP_SOLVE:
        // TODO: Solve the puzzle
        break;
    case SSOLVE_OP_CHECK:
    {
        const check_result_t result = ssolve_check_puzzle(puzzle, color_hints);
        switch (result)
        {
        case SSOLVE_CHECK_UNSOLVED:
            fprintf(stdout, "Puzzle is unsolved:\n");
            break;
        case SSOLVE_CHECK_SOLVED:
            fprintf(stdout, "Puzzle is solved:\n");
            break;
        case SSOLVE_CHECK_INVALID:
            fprintf(stdout, "Puzzle is invalid:\n");
            break;
        }
        break;
    }
    default:
        fprintf(stderr, "Unsupported operation: %d\n", args.op);
        exit(EXIT_FAILURE);
    }

    // Finally, print the solved puzzle
    fprint_puzzle(stdout, puzzle, color_hints, args.color);

    return 0;
}
