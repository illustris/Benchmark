#include <stdio.h>
#include <stdint.h>

#define START_LETTER 33
#define STOP_LETTER 126
#define MAX_LETTERS 64

char *benchmark_word(char *);
short brute_force_hash(int , char , char , uint8_t [16], char *);

void get_candidate(char *, int);
void init_letters(char *, int);
