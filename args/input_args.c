#include "input_args.h"
#include "../utils/utils.h"

input_args get_default_input_args()
{
    input_args args;
    args.processes = 4;
    args.default_flag = 0;
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
    if (s_len(w) > MAX_WORD_LEN)
        close_this(1, "Maximum word length is 5");

    sprintf(args->word, "%s", w);

    return 1;
}

input_args parse_input(int argc, char *argv[])
{
    input_args args = get_default_input_args();
    char opt = 0,
         p_flag = 0,
         w_flag = 0,
         h_flag = 0,
         passed_hash[33] = {0};

    if (argc == 1)
    {
        read_interactive(&args);
        return args;
    }

    while ((opt = getopt(argc, argv, "dp:w:h:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            p_flag = 1;
            if (optarg == NULL)
                close_this(1, "'p' option requires number of processes.");
            args.processes = atoi(optarg);
            if (args.processes < 1)
                close_this(1, "Invalid processes number.");
            break;

        case 'w':
            w_flag = 1;
            if (optarg == NULL)
                close_this(1, "'w' option requires word to benchmark.");

            if (s_len(optarg) > MAX_WORD_LEN)
                close_this(1, "Maximum word length is 5");

            sprintf(args.word, "%s", optarg);
            if (s_len(args.word) < 1 || !is_breakable(args.word))
                close_this(1, "Invalid word.");
            if (args.hash_flag)
                close_this(1, "Concurent options.");
            args.benchmark_flag = 1;
            break;

        case 'd':
            args.default_flag = 1;
            break;

        case 'h':
            if (optarg == NULL)
                close_this(1, "'h' option requires hash to break.");
            if (s_len(optarg) != 32)
                close_this(1, "Invalid hash.");
            sprintf(passed_hash, "%s", optarg);
            if (args.benchmark_flag)
                close_this(1, "Concurent options.");
            args.hash_flag = 1;
            h_flag = 1;
            break;

        default:
            close_this(1, get_help_text());
            break;
        }
    }

    if (argc > 1 && !p_flag && !h_flag && !w_flag && !args.default_flag)
        close_this(1, "Invalid args.");

    if (args.default_flag)
    {
        args = get_default_input_args();
        args.default_flag = 1;
        return args;
    }
    return args;
}
