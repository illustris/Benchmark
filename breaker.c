#include "breaker.h"
#include "md5/skipper.h"
#include "utils/utils.h"

pid_t pid[MAX_LETTERS];
int pipe_fd[MAX_PROCESSES][2];

int do_process_work_break(int id, int len, int fd_id, char start_letter, char stop_letter, uint8_t hash[16])
{
    unsigned long start_time = get_time_miliseconds();
    char word[MAX_LETTERS + 1];
    short result = brute_force_hash(len, start_letter, stop_letter, hash, word);

    printf("| %7d | %5s  | %5s  | %8lu |\n", id, result ? "OK" : "Fail", result ? word : "", get_time_miliseconds() - start_time);
    if (!result)
    {
        close(pipe_fd[fd_id][0]);
        close(pipe_fd[fd_id][1]);
        exit(0);
    }
    close(pipe_fd[fd_id][0]);
    short tmp = write(pipe_fd[fd_id][1], &word, len);
    if (tmp < 0)
        tmp = -1;
    close(pipe_fd[fd_id][1]);
    exit(0);
}

unsigned long make_breaker(uint8_t hash[16], int processes, int len, char *word)
{
    if (word == NULL)
        return 0;
    unsigned long start_time = 0,
                  total_time = 0;
    char start_letters[MAX_PROCESSES];

    for (int i = 0; i < processes; ++i)
        start_letters[i] = START_LETTER + i * ((STOP_LETTER - START_LETTER) / processes);

#ifdef DEBUG
    for (int i = 0; i < processes; ++i)
        printf("i: %d - start letter: %d\n", i, start_letters[i]);
#endif

    printf("| Process | Status |  Word  |   Time   |\n");

    for (int i = 0, k = 0; i < processes; ++i, ++k)
        k = pipe(pipe_fd[i]);

    start_time = get_time_miliseconds();

    for (int i = 0; i < processes; ++i)
        if (!(pid[i] = fork()))
            do_process_work_break(i + 1, len, i, start_letters[i], start_letters[i] + (STOP_LETTER - START_LETTER) / processes, hash);
        else if (pid[i] < 0)
            printf("| %7d | %6s | %5s  | %8d |\n", i + 1, "FAILED", "", 0);

    char buff[MAX_PROCESSES][MAX_LETTERS];
    int solved_word_buff_id = -1;
    for (int i = 0; i < processes; ++i)
    {
        close(pipe_fd[i][1]);
        if (solved_word_buff_id > 0)
        {
            close(pipe_fd[i][0]);
            continue;
        }
        while (read(pipe_fd[i][0], &(buff[i]), len) > 0)
        {
#ifdef DEBUG
            printf("readed %s\n", (buff[i]));
#endif
            if (s_len((buff[i])))
                solved_word_buff_id = i;
        }
    }

    for (int i = 0; i < processes; ++i)
        waitpid(pid[i], NULL, 0);

    total_time = get_time_miliseconds() - start_time;

    for (int i = 0; i < s_len(buff[solved_word_buff_id]); ++i)
        word[i] = buff[solved_word_buff_id][i];
    buff[solved_word_buff_id][len] = 0;
    printf("Word       : %s\n", buff[solved_word_buff_id]);
    printf("Total time : %lu\n", total_time);

    return total_time;
}
