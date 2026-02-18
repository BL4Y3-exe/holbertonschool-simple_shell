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
        return (NULL);

    argv = malloc(bufsize * sizeof(char *));
    if (argv == NULL)
    {
        perror("malloc");
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

char *get_path(void)
{
    int i = 0;

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
            return (environ[i] + 5);
        i++;
    }
    return (NULL);
}

char *find_in_path(char *command)
{
    char *path_env, *path_copy, *dir;
    char full_path[1024];
    struct stat st;

    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return strdup(command);
        return (NULL);
    }
    
    path_env = get_path();
    if (path_env == NULL)
        return (NULL);

    path_copy = strdup(path_env);
    if(path_copy == NULL)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return strdup(full_path);
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
