#include "benchmark.h"
#include "md5/skipper.h"
#include "utils/utils.h"

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

unsigned long make_benchmark(char *word, int processes)
{
    unsigned long start_time = 0,
                  total_time = 0;
    unsigned long long total_hashes = 0;
    printf("| Process | Status |  Word  |   Time   |\n");

    start_time = get_time_miliseconds();

    for (int i = 0; i < processes; ++i)
        if (!(pid[i] = fork()))
            do_process_work(i + 1, word);
        else if (pid[i] < 0)
            printf("| %7d | %6s | %5s  | %8d |\n", i + 1, "FAILED", word, 0);

    for (int i = 0; i < processes; ++i)
        waitpid(pid[i], NULL, 0);

    total_time = get_time_miliseconds() - start_time;
    total_hashes = processes * get_hashes_number(word);

    printf("Total time [ms]: %lu\n", total_time);
    printf("Total hashes   : %llu\n", total_hashes);
    printf("Average hs / ms: %Lf\n", (long double)total_hashes / (long double)total_time);

    return total_time;
}
