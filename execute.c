#include "shell.h"

void execute_command(char *command, char *prog_name, int line_number)
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
        fprintf(stderr, "%s: %d: %s: not found\n",
        argv[0], line_number, argv[0]);
        free(argv);
        exit(127);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(argv);
        free(full_path);
        return;
    }

    if (pid == 0)
    {
        execve(full_path, argv, environ);
        perror(argv[0]);
        exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    free(full_path);
    free(argv);
}