#ifndef PRIME_H
#define PRIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void p_ctrlc(int p_si);
char **parse_command(char *line);
void execute_command(char **args);

#endif /* PRIME_H */
