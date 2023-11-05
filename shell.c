#include "shell.h"

void execute_command(char *cmd) {
    pid_t child_pid;
    int pid_status;

    char **args = malloc(2 * sizeof(char*));
    if (args == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    args[0] = strdup(cmd);  /* Copy the command into args[0] */
    args[1] = NULL;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        if (execvp(cmd, args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &pid_status, 0);
    }

    /*  Free dynamically allocated memory */
    free(args[0]);
    free(args);
}

int main(void) {
    char *cmd = NULL;
    size_t cmdsize = 0;

    while (1) {
        printf("OurShell $ ");
        if (getline(&cmd, &cmdsize, stdin) == -1) {
            printf("\n");
            free(cmd);
            exit(EXIT_SUCCESS);
        }
        cmd[strcspn(cmd, "\n")] = '\0';
        execute_command(cmd);
    }

    free(cmd);
    return 0;
}
