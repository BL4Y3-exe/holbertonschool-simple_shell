#include "shell.h"

void trim_inplace(char *s)
{
    size_t len, start = 0;

    if (s == NULL)
        return;
    
    len = strlen(s);

    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r' ||
    s[len - 1] == ' ' || s[len - 1] == '\t'))
    {
        s[--len] = '\0';
    }

    while (s[start] && (s[start] == ' ' || s[start] == '\t'))
        start++;

    if (start > 0)
        memmove(s, s + start, len - start + 1);
}


char **split_args(char *s)
{
    char *token;
    char **argv = NULL;
    size_t bufsize = 8;
    size_t idx = 0;

    if (s == NULL)
        return;

    argv = malloc(bufsize * sizeof(char *));
    if (argv == NULL)
    {
        perror("malloc")
        return NULL;
    }

    token = strtok(s, " \t");
    while (token != NULL)
    {
        argv[idx++] = token;
        if (idx >= bufsize)
        {
            bufsize *= 2;
            argv = realloc(argv, bufsize * sizeof(char *));
            if (argv == NULL)
            {
                perror("realloc");
                return NULL;
            }
        }
        token = strtok(NULL, " \t");
    }
    argv[idx] = NULL;
    return argv;
}