#include "run_program.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ERROR_CODE 255

int run_program(char *file_path, char *args[]) {
    // Validates if the file_path is not NULL
    if (file_path == NULL) {
        return ERROR_CODE;
    }

    pid_t pid = fork();
    
    // Checks for fork error, returns ERROR_CODE if fork fails
    if (pid < 0) {
        return ERROR_CODE;
    }

    // Executes in the child process
    if (pid == 0) {
        // Attempts to execute the program specified by file_path
        if (execvp(file_path, args) == -1) {
            // If execvp fails, the child process exits with ERROR_CODE
            exit(ERROR_CODE);
        }
    }

    // Executes in the parent process
    int status;
    // Waits for the child process to terminate and checks for errors in waitpid
    if (waitpid(pid, &status, 0) == -1) {
        return ERROR_CODE;
    }

    // Checks if the child process terminated normally
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        // Returns the exit status of the child process
        return exit_status;
    } else {
        // Returns ERROR_CODE if the child process did not terminate normally
        return ERROR_CODE;
    }
}
