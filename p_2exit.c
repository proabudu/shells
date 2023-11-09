#include "prime.h"

/**
 * handle_exit - Used to handle exit with params
 * @args: Should contain only [0] => `exit`
 *        and [1] => `<the exit code>`
 */
void handle_exit(char **args)
{
    int status = 0;

    if (args[1] != NULL)
        status = atoi(args[1]);
    exit(status);
}
