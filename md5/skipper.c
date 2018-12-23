#include "skipper.h"
#include "../utils/utils.h"
#include "md5.h"

void init_letters(char *letters, int len)
{
    for (int i = 0; i < len; ++i)
        *(letters + i) = START_LETTER;
}

void get_candidate(char *candidate, int len)
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
    char letters[MAX_LETTERS] = {0};
    uint8_t word_hash[16] = {0},
            candidate_hash[16] = {0};

    md5((uint8_t *)word, len, (uint8_t *)word_hash);
    init_letters(letters, len);

    while (!compare(word_hash, md5((uint8_t *)letters, len, (uint8_t *)candidate_hash)))
    {
        get_candidate(letters, len);
    }
#ifdef DEBUG
    printf("Candidate hash: ");
    print_hash(candidate_hash);
    printf("Word hash     : ");
    print_hash(word_hash);
#endif

    return word;
}

short brute_force_hash(int len, char start_letter, char stop_letter, uint8_t to_break_hash[16], char *broken_word)
{
    uint8_t candidate_hash[16] = {0};
    char letters[MAX_LETTERS] = {0};
    init_letters(letters, len);
    letters[len - 1] = start_letter;
#ifdef DEBUG
    printf("stop_letter - %c\n", (char)stop_letter);
    printf("letters: %s\n%d\n", letters, letters[0]);
#endif
    while (!compare(to_break_hash, md5((uint8_t *)letters, len, candidate_hash)))
    {
        get_candidate(letters, len);
        if (letters[len - 1] >= stop_letter)
        {
#ifdef DEBUG
            printf("fail - %d\nletters - %s\n", letters[0], letters);
#endif
            return 0;
        }
    }
#ifdef DEBUG
    printf("Broken: %s\n", letters);
#endif
    for (int i = 0; i < len; ++i)
        broken_word[i] = letters[i];

    return 1;
}
