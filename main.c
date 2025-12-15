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
    //fputs("Hello, world", file_ptr);
    char* buffer = (char*)calloc(256, sizeof(char));
    if (buffer == NULL) {
        perror("memory error\n");
        return EXIT_FAILURE;
    }
    char* line = NULL;
    size_t capacity = 0;
    while (getline(&line, &capacity, file_ptr) != -1) {
        strcat(buffer, line);
    }
    fputs(buffer, stdout);
    printf("\n");
    free(line);
    fclose(file_ptr);
    
    Command C;
    C = command(argv[2]);
    printf("%d %s %s\n", C.cnum, C.str1, C.str2);
    switch(C.cnum){
        case 0:
            perror("command error\n");
            return EXIT_FAILURE;
        case 1:
            deleteStr(buffer, C.str1);
            break;
        case 2:
            addPrefix(buffer, C.str1);
            break;
        case 3:
            addSuffix(buffer, C.str1);
            break;
        case 4:
            replace(buffer, C.str1, C.str2);
//            fputs(buffer, stdout);
//            printf("\n");
            break;
    }
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    
    file_ptr = fopen(argv[1], "w");
    if (file_ptr == NULL) {
        perror("file error\n");
        return EXIT_FAILURE;
    }
    fputs(buffer, file_ptr);
    fputs(buffer, stdout);
    printf("\n");
    free(buffer);
    fclose(file_ptr);
    return EXIT_SUCCESS;
}
