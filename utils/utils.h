#include <stdint.h>
#include <sys/time.h>

#define MAX_PROCESSES 64

void show_help();
void close_this(int, char *);
void print_hash(uint8_t *);

int s_len(char *);

short is_breakable(char *);
short compare(uint8_t *, uint8_t *);

unsigned long get_time_miliseconds();

unsigned long long long_pow(unsigned long long, int);
unsigned long long get_hashes_number(char *);

char *get_help_text();
