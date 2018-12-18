typedef struct
{
    int processes;
    char word[64];
} input_args;

input_args get_default_input_args();
input_args parse_input(int, char **);
int read_interactive(input_args *);
