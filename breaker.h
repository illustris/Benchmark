#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/wait.h>

unsigned long make_breaker(uint8_t[16], int, int, char *);

int do_process_work_break(int, int, int, char, char, uint8_t[16]);