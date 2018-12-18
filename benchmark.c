#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "args/input_args.h"
#include "utils/utils.h"
#include "md5/skipper.h"

#define MAX_PROCESSES 64
pid_t pid[MAX_PROCESSES];
short ready = 0;

int do_process_work(int id, char *word)
{
#ifdef DEBUG
    printf("Proc %d waiting\n", id);
#endif
    // while (!ready)
    //     ;
#ifdef DEBUG
    printf("Proc %d started\n", id);
#endif
    unsigned long start_time = get_time_miliseconds();
    benchmark_word(word);
    printf("| %7d | %8lu |\n", id, get_time_miliseconds() - start_time);
    exit(0);
}

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
    for (int i = 0; i < args.processes; ++i)
    {
        if (!(pid[i] = fork()))
        {
            do_process_work(i + 1, args.word);
        }
    }
    printf("| Process |   Time   |\n");
    ready = 1;
    for (int i = 0; i < args.processes; ++i)
    {
        waitpid(pid[i], NULL, 0);
    }
    return 0;
}
