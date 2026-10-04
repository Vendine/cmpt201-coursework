#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HSIZE 5

void free_h(char *history[], int curSize);
void print_h(char *history[], int curSize);
void add_h(char *history[], int *curSize, char *input);

int main(void){
    char *history[HSIZE];
    int curSize = 0;
    
    while(true){
        char *input = NULL;
        size_t cap = 0;
        
        printf("Enter input: ");
        fflush(stdout);
        size_t len = getline(&input, &cap, stdin);
        if (len < 0){
            free(input);
            free_h(history, curSize);
            break;
        } 

        add_h(history, &curSize, input);
        if(strcmp(input, "print\n") == 0){
            print_h(history, curSize);
        }
    } 
    
    return 0;
}

void free_h(char *history[], int curSize){
    if(!history){
        return;
    }
    for(int i = 0; i < curSize; i++){
        free(history[i]);
    }
}

void print_h(char *history[], int curSize){
    if(!history){
        return;
    }
    for(int i = 0; i < curSize; i++){
        printf("%s", history[i]);
    }
}

void add_h(char *history[], int *curSize, char *input){
    if(!history || !input || !curSize){
        return;
    }
    if(*curSize >= HSIZE){
        free(history[0]);
        for(int i = 0; i < *curSize - 1; i++){
            history[i] = history[i + 1];
        }
        history[HSIZE - 1] = input;
    }
    else{
        history[(*curSize)++] = input;
    }
}
