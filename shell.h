#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

void print_promt(void);
void execute_command(char *command);
void trim_inplace(char *s);

#endif
