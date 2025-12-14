#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
        printf("%s ", strsplit[i]);
        token = strtok_r(NULL, "/", &saveptr);
        if (token){
            i++;
        }
    }
    printf("\n");
    if (i == 1 && strcmp(strsplit[1], "d") == 0){
        Command C = {1, strsplit[0], "-"};
        return C;
    }
    if (i == 2) {
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "prefix") == 0) {
            Command C = {2, strsplit[1], "-"};
            return C;
        }
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "suffix") == 0) {
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

char* replace(char* buffer, char* substr, char* newstr){
    regex_t regex;
    regmatch_t m;
    if (regcomp(&regex, substr, REG_EXTENDED)) {
        perror("regex compilation error");
        return "";
    }
    while(regexec(&regex, buffer, 1, &m, 0) != REG_NOMATCH) {
        long long start = m.rm_so;
        long long end = m.rm_eo;
        //printf("%ld %ld\n", start, end);
        char* buffer1 = (char*)calloc(256, sizeof(char));
        if (buffer1 == NULL) {
            perror("memory error\n");
            return "";
        }
        
        for(int i = 0; i < strlen(buffer) + strlen(newstr) - (end - start); i++) {
            if (i < start) {
                buffer1[i] = buffer[i];
            }
            if (i >= start && i < start + strlen(newstr)) {
                buffer1[i] = newstr[i - start];
            }
            if (i >= start + strlen(newstr)) {
                buffer1[i] = buffer[i + end - start - strlen(newstr)];
            }
        }
        strcpy(buffer, buffer1);
        //fputs(buffer, stdout);
        //printf("\n");
        free(buffer1);
    }
    //fputs(buffer, stdout);
    regfree(&regex);
    return buffer;
}
char* deleteStr(char* buffer, char* str, char* newstr){
    return buffer;
}
char* addPrefix(char* buffer, char* newstr){
    return buffer;
}
char* addSuffix(char* buffer, char* newstr){
    return buffer;
}
