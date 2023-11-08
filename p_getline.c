#include "prime.h"

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;
static size_t chars_read = 0;

char *custom_getline(void) {
    size_t i = 0;
    char *line = NULL;
    int newline_found = 0;

    while (1) {
        if (buffer_index >= chars_read) {
            buffer_index = 0;
            chars_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (chars_read == 0) {
                if (line) {
                    free(line);
                }
                return NULL;  /* End of file */
            }
            else if (chars_read == (size_t)-1) {
                perror("read");
                if (line) {
                    free(line);
                }
                exit(EXIT_FAILURE);  /* Error reading from input */
            }
        }

        for (; buffer_index < chars_read; ++buffer_index) {
            if (buffer[buffer_index] == '\n') {
                newline_found = 1;
                buffer_index++;
                break;
            }
            i++;
        }

        /* Allocate memory for the line and copy characters */
        if (newline_found) {
            line = malloc(i + 1);
            if (line == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);  /* Allocation error */
            }
            strncpy(line, buffer + buffer_index - i - 1, i);
            line[i] = '\0';
            break;
        }
    }

    return line;
}
