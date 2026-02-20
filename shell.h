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
int execute_command(char *command, char *prog_name, int line_number);
void trim_inplace(char *s);
char **split_args(char *s);
char *find_in_path(char *command);
char *get_path(void);


#endif
