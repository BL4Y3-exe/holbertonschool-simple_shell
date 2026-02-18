#include "shell.h"

void execute_command(char *command)
{
    pid_t pid;
    int status;
    char **argv;
    char *full_path;

    if (command == NULL)
        return;

    argv = split_args(command);
    if (argv == NULL || argv[0] == NULL)
    {
        free(argv);
        return;
    }

    full_path = find_in_path(argv[0]);
    if (full_path == NULL)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
        free(argv);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error");
        free(argv);
        return;
    }

    if (pid == 0)
    {
        execve(argv[0], argv, environ);
        perror(argv[0]);
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
        free(argv);
    }
}