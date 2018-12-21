#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "args/input_args.h"
#include "utils/utils.h"
#include "md5/skipper.h"
#include "benchmark.h"

void validate_args(input_args args)
{
#ifdef DEBUG
    printf("Proc %d\nWord: %s\n", args.processes, args.word);
#endif
    if (args.processes > 64)
        close_this(1, "Invalid args.");
}

int main(int argc, char *argv[])
{
    input_args args = parse_input(argc, argv);
    validate_args(args);

    if (args.default_flag || args.benchmark_flag)
    {
        make_benchmark(args.word, args.processes);
        close_this(0, "Bye! ;)");
    }
    else if (args.hash_flag)
    {
    }
    return 0;
}