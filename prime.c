#include "prime.h"

void p_ctrlc(int p_si)
{
    (void)p_si;
    printf("\n$ ");
    fflush(stdout);
}

char **parse_command(char *line)
{
    char **args = NULL;
    char *token = NULL;
    size_t p = 0;

    args = malloc(sizeof(char *) * 64);
    if (args == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL) {
        args[p] = strdup(token);
        if (args[p] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " ");
        p++;
    }
    args[p] = NULL;

    return args;
}

void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(pid, &status, 0);
    }
}

int main(void)
{
    char *line = NULL;
    size_t linesize = 0;
    ssize_t read_bytes;

    signal(SIGINT, p_ctrlc);

    while (1)
    {
        printf("$ ");
        read_bytes = getline(&line, &linesize, stdin);

        if (read_bytes == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] != '\0')
        {
            char **args = parse_command(line);
            if (args)
            {
                execute_command(args);
                free(args);
            }
        }

        free(line);
        line = NULL;
        linesize = 0;
    }

    return 0;
}
