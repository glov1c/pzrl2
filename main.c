#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operations.h"


int main(int argc, char** argv) {
    if (argc != 3) {
        perror("not correct arguments\n");
        return EXIT_FAILURE;
    }
    FILE* file_ptr = fopen(argv[1], "a");
    if (file_ptr == NULL) {
        perror("file error\n");
        return EXIT_FAILURE;
    }
    
    char* buffer = (char*)calloc(128, sizeof(char));
    if (buffer == NULL) {
        perror("memory error\n");
        return EXIT_FAILURE;
    }
    
    Command C;
    C = command(argv[2]);
    switch(C.cnum){
        case 0:
            perror("command error\n");
            return EXIT_FAILURE;
        case 1:
            deleteStr(buffer, C.str1);
        case 2:
            addPrefix(buffer, C.str1);
        case 3:
            addSuffix(buffer, C.str1);
        case 4:
            replace(buffer, C.str1, C.str2);
    }
    fclose(file_ptr);
    return EXIT_SUCCESS;
}
