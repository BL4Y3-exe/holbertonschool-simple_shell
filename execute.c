#include "shell.h"

void execute_command(char *command)
{
    pid_t pid;
    char *argv[2];

    argv[0] = command;
    argv[1] = NULL;

    pid = firk();
    if (pid == -1)
    {
        perror("Error");
        return;
    }

    if (pid == 0)
    {
        if (execve(command, argv, environ) == -1)
            perror(command);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}