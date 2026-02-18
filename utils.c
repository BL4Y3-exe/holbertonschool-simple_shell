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