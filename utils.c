#include "shell.h"

void remove_newline(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
        i++;
    }
}