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
    char** buffer = (char**)calloc(100, sizeof(char*));
    if (buffer == NULL) {
        perror("memory error\n");
        return EXIT_FAILURE;
    }
    char* line = NULL;
    size_t capacity = 0;
    int bufferSize = 0;
    while (getline(&line, &capacity, file_ptr) != -1) {
        if (line[strlen(line)-1] == '\n') {
            line[strlen(line)-1] = '\0';
        }
        buffer[bufferSize] = strdup(line);
//        fputs(buffer[bufferSize], stdout);
//        printf("\n");
        bufferSize++;
        line = NULL;
    }
    
    free(line);
    fclose(file_ptr);
    
    Command C;
    C = command(argv[2]);
//    printf("%d %s %s\n", C.cnum, C.str1, C.str2);
    switch(C.cnum){
        case 0:
            perror("command error\n");
            return EXIT_FAILURE;
        case 1:
            deleteStr(buffer, &bufferSize, C.str1);
            break;
        case 2:
            addPrefix(buffer, bufferSize, C.str1);
            break;
        case 3:
            addSuffix(buffer, bufferSize, C.str1);
            break;
        case 4:
            replace(buffer, bufferSize, C.str1, C.str2);
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
    for(int i = 0; i < bufferSize; i++) {
//        fputs(buffer[i], file_ptr);
//        fputs("\n", file_ptr);
//        fputs(buffer[i], stdout);
//        fputs("\n", stdout);
    }
    free(buffer);
    fclose(file_ptr);
    return EXIT_SUCCESS;
}
