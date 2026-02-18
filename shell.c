#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
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
        
        execute_command(line);
    }

    free(line);
    return (0);
}
