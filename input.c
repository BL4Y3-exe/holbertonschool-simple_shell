#include "shell.h"

void print_promt(void)
{
    if (isatty(STDIN_FILENO))
        printf("($) ");
}