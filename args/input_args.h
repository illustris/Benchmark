#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_WORD_LEN 5

typedef struct
{
    int processes,
        len;
    char word[64],
        default_flag,
        hash_flag,
        benchmark_flag;
    uint8_t input_hash[16];
} input_args;

input_args get_default_input_args();
input_args parse_input(int, char **);

int read_interactive(input_args *);
