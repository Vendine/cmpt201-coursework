#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    while(true){    
        char *str = NULL;
        size_t size = 0; 
        char *saveptr = NULL;

        printf("Please enter some text: ");
        
        ssize_t len = getline(&str, &size, stdin);
        if (len == -1) {
            perror("getline failed");
            exit(EXIT_FAILURE);
        }
        
        char *tokens = strtok_r(str, " ", &saveptr);

        printf("Token:");

        while(tokens != NULL){
            printf(" \n%s", tokens);
            tokens = strtok_r(NULL, " ", &saveptr);
        }
        free(str); 
    }

    return 0;
}