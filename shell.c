#include "shell.h"

void execute_command(char *cmd) {
    pid_t child_pid;
    int pid_status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
    } else if (child_pid == 0) {
        char *args[] = {cmd, NULL};
        if (execvp(cmd, args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        waitpid(child_pid, &pid_status, 0);
    }
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
