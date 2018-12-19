#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "args/input_args.h"
#include "utils/utils.h"
#include "md5/skipper.h"

#define MAX_PROCESSES 64
pid_t pid[MAX_PROCESSES];

int do_process_work(int id, char *word)
{
#ifdef DEBUG
    printf("Proc %d started\n", id);
#endif
    unsigned long start_time = get_time_miliseconds();
    benchmark_word(word);
    printf("| %7d | %5s  | %5s  | %8lu |\n", id, "OK", word, get_time_miliseconds() - start_time);

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
    unsigned long start_time = 0,
                  total_time = 0;
    unsigned long long total_hashes = 0;
    input_args args = parse_input(argc, argv);

    validate_args(args);
    printf("| Process | Status |  Word  |   Time   |\n");

    start_time = get_time_miliseconds();

    for (int i = 0; i < args.processes; ++i)
        if (!(pid[i] = fork()))
            do_process_work(i + 1, args.word);
        else if (pid[i] < 0)
            printf("| %7d | %6s | %5s  | %8d |\n", i + 1, "FAILED", args.word, 0);

    for (int i = 0; i < args.processes; ++i)
        waitpid(pid[i], NULL, 0);

    total_time = get_time_miliseconds() - start_time;
    total_hashes = args.processes * get_hashes_number(args.word);

    printf("Total time [ms]: %lu\n", total_time);
    printf("Total hashes   : %llu\n", total_hashes);
    printf("Average hs / ms: %Lf\n", (long double)total_hashes / (long double)total_time);

    return 0;
}
