#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operations.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        perror("not correct arguments\n");
        return EXIT_FAILURE;
    }
    FILE* file_ptr = fopen(argv[1], "r");
    if (file_ptr == NULL) {
        perror("file error\n");
        return EXIT_FAILURE;
    }
    
    char* buffer = (char*)calloc(128, sizeof(char));
    if (buffer == NULL) {
        perror("memory error\n");
        return EXIT_FAILURE;
    }
    
    fclose(file_ptr);
    return EXIT_SUCCESS;
}
