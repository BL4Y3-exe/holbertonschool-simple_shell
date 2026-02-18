#include "shell.h"

void execute_command(char *command)
{
    pid_t pid;
    int status;
    char **argv;

    if (command == NULL)
        return;

    argv = split_args(command);
    if (argv == NULL)
        return;

    if (argv[0] == NULL)
    {
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