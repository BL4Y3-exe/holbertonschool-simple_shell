#include "shell.h"

int execute_command(char *command, char *prog_name, int line_number)
{
    pid_t pid;
    int status;
    char **argv;
    char *full_path;

    if (command == NULL)
        return (0);

    argv = split_args(command);
    if (argv == NULL)
        return (0);

    if (argv[0] == NULL)
    {
        free(argv);
        return (0);
    }

    full_path = find_in_path(argv[0]);
    if (full_path == NULL)
    {
        fprintf(stderr, "%s: %d: %s: not found\n",
                prog_name, line_number, argv[0]);
        free(argv);

        if (!isatty(STDIN_FILENO))
            return (127);
        return (0);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(argv);
        free(full_path);
        return (0);
    }

    if (pid == 0)
    {
        execve(full_path, argv, environ);
        perror(argv[0]);
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(full_path);
    free(argv);
    return (0);
}