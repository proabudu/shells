#include "prime.h"

void handle_exit(char **args) {
    int status = 0;
    
    /* Check if there is an argument for exit status */
    if (args[1] != NULL) {
        /* Convert the status argument to an integer */
        status = atoi(args[1]);
    }
    
    /* Exit the shell with the specified status  code */
    exit(status);
}
