#include "run_program.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ERROR_CODE 255

int run_program(char *file_path, char *args[]) {
    // Check if file_path is NULL
    if (file_path == NULL) {
        return ERROR_CODE;
    }

    // Ensure the first argument is the program name
    // Ensure args is not NULL and the first argument is the program name
if (args != NULL && args[0] == NULL) args[0] = file_path;

    pid_t pid = fork();
    
    // Error in fork
    if (pid < 0) {
        return ERROR_CODE;
    }

    // Child process
    if (pid == 0) {
        // Execute the program
        if (execvp(file_path, args) == -1) {
            // In case of an error in execvp, exit with ERROR_CODE
            exit(ERROR_CODE);
        }
    }

    // Parent process
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        // Error in waitpid
        return ERROR_CODE;
    }

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        // Return the exit status of the child process
        return exit_status;
    } else {
        // If the child process did not terminate normally, return ERROR_CODE
        return ERROR_CODE;
    }
}
