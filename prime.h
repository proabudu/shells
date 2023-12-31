#ifndef SHELL_PRIME_H
#define SHELL_PRIME_H

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printer(const char *str);
void p_ctrlc(int p_si);
char **parse_cmd(char *p_line);
void p_exec(char **p_args);
void p_env(void);
void p_exit(void);
void p_line_error(int p_read_bytes, char *p_line);
void parse_command(char *input, char **args, int *num_args);
void handle_exit(char **args);
char *_strtok(char *str, char *delim);


extern char **environ;

#endif /* SHELL_PRIME_H */
