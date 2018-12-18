#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "input_args.h"
#include "../utils/utils.h"

input_args get_default_input_args()
{
    input_args args;
    args.processes = 4;
    sprintf(args.word, "%s", "koko");
    return args;
}

int read_interactive(input_args *args)
{
    int p = 0;
    char w[64];
    printf("Number of processes: ");
    if (scanf("%d", &p) != 1 || p < 1)
        close_this(1, "Invalid number.");
    printf("Word: ");
    if (scanf("%s", w) != 1 || !is_breakable(w))
        close_this(1, "Invalid word.");
    args->processes = p;
    sprintf(args->word, "%s", w);
    return 1;
}

input_args parse_input(int argc, char *argv[])
{
    input_args args = get_default_input_args();
    char opt = 0;
    if (argc == 1)
    {
        read_interactive(&args);
    }
    while ((opt = getopt(argc, argv, "p:w:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            if (optarg == NULL)
                close_this(1, "'p' option requires number of processes.");
            args.processes = atoi(optarg);
            if (args.processes < 1)
                close_this(1, "Invalid processes number.");
            break;
        case 'w':
            if (optarg == NULL)
                close_this(1, "'w' option requires word to benchmark.");
            sprintf(args.word, "%s", optarg);
            if (s_len(args.word) < 1 || !is_breakable(args.word))
                close_this(1, "Invalid word.");
            break;
        default:
            close_this(1, get_help_text());
            break;
        }
    }
    return args;
}
