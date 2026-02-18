#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

void print_promt(void);
void execute_command(char *command);
void trim_inplace(char *s);
char **split_args(char *s);
char *find_in_path(char *command);


#endif
