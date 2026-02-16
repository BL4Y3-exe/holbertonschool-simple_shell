#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        print_promt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            free(line);
            exit(0);
        }
        
        remove_newline(line);

        if (line[0] == "\0")
            continue;
        
        execute_command(line);
    }

    return (0);
}

