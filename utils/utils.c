#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int s_len(char *input)
{
    int i = 0;
    for (; *(i + input) != 0; ++i)
        ;
    return i;
}

void close_this(int code, char *message)
{
    if (s_len(message))
        printf("%s\n", message);
    exit(code);
}

short is_breakable(char *input)
{
    for (int i = 0; *(input + i) != 0; ++i)
        if (*(input + i) < 33 || *(input + i) > 126)
            return 0;
    return 1;
}

char *get_help_text()
{
    return "Usage:\nex: benchmark -p 7 -w kill";
}

void show_help()
{
    printf("%s\n", get_help_text());
}

short compare(uint8_t *a, uint8_t *b)
{
    for (int i = 0; i < 16; ++i)
        if (*(a + i) != *(b + i))
            return 0;
    return 1;
}

void print_hash(uint8_t *hash)
{
    printf("%2.2x%2.2x%2.2x%2.2x", hash[0], hash[1], hash[2], hash[3]);
    printf("%2.2x%2.2x%2.2x%2.2x", hash[4], hash[5], hash[6], hash[7]);
    printf("%2.2x%2.2x%2.2x%2.2x", hash[8], hash[9], hash[10], hash[11]);
    printf("%2.2x%2.2x%2.2x%2.2x\n", hash[12], hash[13], hash[14], hash[15]);
}

unsigned long get_time_miliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)tv.tv_sec * 1000 + (unsigned long)tv.tv_usec / 1000;
}
