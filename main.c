#include "ssolve/check.h"
#include "ssolve/parse.h"
#include "ssolve/puzzle.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum ssolve_operation_t
{
    SSOLVE_OP_SOLVE = 0,  // default
    SSOLVE_OP_CHECK,
} ssolve_operation_t;

typedef struct ssolve_cli_args_t
{
    ssolve_operation_t op;
    ssolve_color_when_t color;
    ssolve_file_format_t format;
    const char* puzzle;
} ssolve_cli_args_t;

void ssolve_usage(void)
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
    printf("\t--format, -f   The input file format. One of 'grid', or 'line'\n");
    printf("\t--check, -c    Instead of solving, check the validity of the given puzzle\n");
    printf("\t--color, -C    When to color the output. 'never', 'auto', or 'always'\n");

    // TODO: Add --generate?
}

ssolve_cli_args_t ssolve_parse_args(int argc, char* argv[])
{
    ssolve_cli_args_t args = {0};

    struct option options[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"format", required_argument, NULL, 'f'},
        {"check", no_argument, NULL, 'c'},
        {"color", required_argument, NULL, 'C'},
        {NULL, 0, NULL, 0},
    };

    while (true)
    {
        int option_index = 0;

        int retval = getopt_long(argc, argv, "hvf:cC:", options, &option_index);
        if (retval == -1)
        {
            break;
        }

        switch (retval)
        {
        case 'h':
            ssolve_usage();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            ssolve_verbose_g = true;
            break;
        case 'f':
            if (strcmp(optarg, "grid") == 0)
            {
                args.format = SSOLVE_FORMAT_GRID;
            } else if (strcmp(optarg, "line") == 0)
            {
                args.format = SSOLVE_FORMAT_LINE;
            } else
            {
                fprintf(stderr, "Unknown argument to --format: '%s'\n", optarg);
                exit(EXIT_FAILURE);
            }
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
    const ssolve_cli_args_t args = ssolve_parse_args(argc, argv);
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

    int parsed_puzzles = 0;
    while (true)
    {
        ssolve_puzzle_t puzzle = {0};
        ssolve_puzzle_t color_hints = {0};
        const bool more_left_to_parse = ssolve_parse_puzzle(file, args.format, puzzle);
        if (more_left_to_parse)
        {
            ++parsed_puzzles;
        } else
        {
            // There's no more to parse. If we parsed zero puzzles, that's a failure
            if (parsed_puzzles == 0)
            {
                fprintf(stderr, "Failed to parse any puzzles\n");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }

        switch (args.op)
        {
        case SSOLVE_OP_SOLVE:
        {
            // TODO: Solve the puzzle

            // Check the newly solved puzzle to set the color hints
            ssolve_check_puzzle(puzzle, color_hints);
            break;
        }
        case SSOLVE_OP_CHECK:
        {
            const ssolve_check_result_t result = ssolve_check_puzzle(puzzle, color_hints);
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
        if (parsed_puzzles > 1)
        {
            printf("\n");
        }
        ssolve_fprint_puzzle(stdout, puzzle, color_hints, args.color);
    }

    return 0;
}
