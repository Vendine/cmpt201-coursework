#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define EXTRA_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 128

struct header { 
    uint64_t size; 
    struct header* next; 
};

void print_out(char *format, void *data, size_t data_size);
void handle_error(const char *message);

int main() {
    void* memory = sbrk(EXTRA_SIZE);
    
    if(memory == (void*)-1){
        handle_error("sbrk failed");
    }

    struct header *block1 = (struct header *)memory;
    struct header *block2 = (struct header *)((char *)memory + BLOCK_SIZE);
    block1->size = BLOCK_SIZE;
    block1->next = NULL;
    block2->size = BLOCK_SIZE;
    block2->next = block1;
    size_t size_h = sizeof(struct header);
    size_t size_d = BLOCK_SIZE - size_h;
    
    memset((char *)block1 + size_h, 0, size_d);
    memset((char *)block2 + size_h, 1, size_d);
    
    print_out("first block:       %p\n", &block1, sizeof(block1));
    print_out("second block:      %p\n", &block2, sizeof(block2));
    print_out("first block size:  %lu\n", &block1->size, sizeof(block1->size));
    print_out("first block next:  %p\n", &block1->next, sizeof(block1->next));
    print_out("second block size: %lu\n", &block2->size, sizeof(block2->size));
    print_out("second block next: %p\n", &block2->next, sizeof(block2->next));

    for (size_t i = 0; i < size_d; i++) {
        char *data = (char *)block1 + size_h + i;
        char buf[BUF_SIZE];
        ssize_t len = snprintf(buf, sizeof(buf), "%d\n", (char)*data);
        if (len < 0) {
            handle_error("snprintf failed");
        }
        write(STDOUT_FILENO, buf, len);
    }
    for (size_t i = 0; i < size_d; i++) {
        char *data = (char *)block2 + size_h + i;
        char buf[BUF_SIZE];
        ssize_t len = snprintf(buf, sizeof(buf), "%d\n", (char)*data);
        if (len < 0) {
            handle_error("snprintf failed");
        }
        write(STDOUT_FILENO, buf, len);
    }

    return 0;
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                          data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                        : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}