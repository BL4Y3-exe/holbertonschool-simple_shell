#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;

    while (1)
    {
        line_number++;

        if (isatty(STDIN_FILENO))
            print_promt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            free(line);
            exit(0);
        }
        
        trim_inplace(line);

        if (line[0] == '\0')
            continue;
        
        execute_command(line, argv[0], line_number);
    }

    free(line);
    return (0);
}
