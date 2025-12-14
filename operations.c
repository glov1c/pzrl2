#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cnum;
    char* str1;
    char* str2;
} Command;

Command command(char* str) {
    char** strsplit = (char**)calloc(3, sizeof(char*));
    char *saveptr;
    char *token = strtok_r(str, "/", &saveptr);
    int i = 0;
    while (token && i < 3) {
        strsplit[i] = token;
        printf("%s ", token);
        token = strtok_r(NULL, "/", &saveptr);
    }
    if (i == 1 && strcmp(strsplit[1], "d") == 0){
        Command C = {1, strsplit[0], "-"};
        return C;
    }
    if (i == 2) {
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "prefix")) {
            Command C = {2, strsplit[1], "-"};
            return C;
        }
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "suffix")) {
            Command C = {3, strsplit[1], "-"};
            return C;
        }
        else{
            Command C = {4, strsplit[1], strsplit[2]};
            return C;
        }
    }
                
    Command C = {0, "-", "-"};
    return C;
}

char* replace(char* buffer, char* substr, char* newstr);
char* deleteStr(char* buffer, char* str, char* newstr);
char* addPrefix(char* buffer, char* newstr);
char* addSuffix(char* buffer, char* newstr);
