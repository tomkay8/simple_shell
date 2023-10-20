#include "shell.h"

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    
    char *error; /* Declare error variable here*/
    
    while (1) {
        char prompt[] = "$ "; /* Display the prompt*/
        write(STDOUT_FILENO, prompt, 2);
        
        nread = getline(&buffer, &bufsize, stdin);
        if (nread == -1) {
            if (feof(stdin)) {
                char newline = '\n';
                write(STDOUT_FILENO, &newline, 1); /* User pressed Ctrl+D*/
                break;
            }
            error = "getline error\n"; /* Assign value here*/
            write(STDOUT_FILENO, error, 14);
            exit(EXIT_FAILURE);
        }
        
        /* Remove the newline character*/
        if (buffer[nread - 1] == '\n') {
            buffer[nread - 1] = '\0';
        }
        
        /* Execute the command*/
        if (execute_command(buffer) == -1) {
            error = "Command not found\n"; /* Assign value here*/
            write(STDOUT_FILENO, error, 18);
        }
    }
    
    free(buffer);
    return 0;
}

