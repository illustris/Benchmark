#include "skipper.h"
#include "utils.h"
#include "md5.h"

void init_letters(char *letters, int len)
{
    for (int i = 0; i < len; ++i)
        *(letters + i) = START_LETTER;
}

void get_candidate(char *candidate, unsigned long long counter, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (candidate[i] < STOP_LETTER)
        {
            ++candidate[i];
            break;
        }
        else
        {
            candidate[i] = START_LETTER;
        }
    }
}

char *benchmark_word(char *word)
{
    int len = s_len(word);
    unsigned long long counter = 0;
    char letters[MAX_LETTERS] = {0};
    uint8_t word_hash[16] = md5((uint8_t *)word, len, &word_hash),
            candidate_hash[16] = {0};

    init_letters(letters, len);
    while(!compare(word_hash, md5((uint8_t*)letters, len, &candidate_hash)))
    {
        get_candidate(letters, counter, len);
        ++counter;
    }
}
