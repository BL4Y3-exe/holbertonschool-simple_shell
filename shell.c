#include "shell.h"

int last_status = 0;

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;
    int rc;
    
    (void)argc;

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

        rc = execute_command(line, argv[0], line_number);
        if (rc == EXIT_SHELL)
        {
            free(line);
            exit(last_status);
        }
        if (rc == 127 && !isatty(STDIN_FILENO))
        {
            free(line);
            exit(127);
        }
    }

    free(line);
    return (0);
}
