#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    while(true){  
        char *program = NULL;
        size_t size = 0; 

        printf("Enter programs to run.\n");
        printf("> ");
        ssize_t len = getline(&program, &size, stdin);
        if (len == -1) {
            perror("getline failed");
            exit(EXIT_FAILURE);
        }
        
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            free(program);
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            execlp(program, program, (char *)NULL);
            perror("Exec failure\n");
            free(program);
            exit(EXIT_FAILURE);
        }

        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid failed");
            free(program);
            exit(EXIT_FAILURE);
        }

        free(program);
    }

    return 0;
}