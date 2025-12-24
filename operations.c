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
    char *token = strtok(str, "/");
    int i = 0;
    while (token && i < 3) {
        strsplit[i] = token;
//        printf("%s ", strsplit[i]);
        token = strtok(NULL, "/");
        if (token){
            i++;
        }
    }
//    printf("\n");
    if (i == 1 && strcmp(strsplit[1], "d") == 0){
        Command C = {1, strsplit[0], NULL};
    	free(token);
    	free(strsplit);
        return C;

    }
    if (i == 2) {
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "prefix") == 0) {
            Command C = {2, strsplit[1], NULL};
    	    free(token);
    	    free(strsplit);
            return C;
        }
        if (strcmp(strsplit[0], "s") == 0 && strcmp(strsplit[2], "suffix") == 0) {
            Command C = {3, strsplit[1], NULL};
            free(token);
    	    free(strsplit);
            return C;
        }
        else{
            Command C = {4, strsplit[1], strsplit[2]};
            free(token);
            free(strsplit);
            return C;
        }
    }
                
    Command C = {0, "-", "-"};
    free(token);
    free(strsplit);
    return C;
}

char** replace(char** buffer, int bufferSize, char* substr, char* newstr){
    regex_t regex;
    regmatch_t m;
    
    if (regcomp(&regex, substr, REG_EXTENDED)) {
        perror("regex compilation error");
        return NULL;
    }
    for(int k = 0; k < bufferSize; k++){
        while(regexec(&regex, buffer[k], 1, &m, 0) != REG_NOMATCH) {
            long long start = m.rm_so;
            long long end = m.rm_eo;
            char* buffer1 = (char*)calloc(256, sizeof(char));
            if (buffer1 == NULL) {
                perror("memory error\n");
                return NULL;
            }
            
            for(int i = 0; i < strlen(buffer[k]) + strlen(newstr) - (end - start); i++) {
                if (i < start) {
                    buffer1[i] = buffer[k][i];
                }
                if (i >= start && i < start + strlen(newstr)) {
                    buffer1[i] = newstr[i - start];
                }
                if (i >= start + strlen(newstr)) {
                    buffer1[i] = buffer[k][i + end - start - strlen(newstr)];
                }
            }
            strcpy(buffer[k], buffer1);
            free(buffer1);
        }
    }
    regfree(&regex);
    return buffer;
}

char** deleteStr(char** buffer, int* bufferSize, char* substr){
    regex_t regex;
    char* regexstr = malloc((strlen(substr) + 2) * sizeof(char));
    if (regexstr == NULL) {
        printf("memory error\n");
        return NULL;
    }
    *regexstr = '\0';
    strcat(regexstr, "^");
    strcat(regexstr, substr);
    strcat(regexstr, "$");
    if (regcomp(&regex, regexstr, REG_EXTENDED)) {
        perror("regex compilation error");
        return NULL;
    }
    
    int countWritten = 0;
    for(int k = 0; k < *bufferSize; k++) {
        char* buffer1 = (char*)calloc(256, sizeof(char));
        if (buffer1 == NULL) {
            perror("memory error\n");
            return NULL;
        }
        int result = regexec(&regex, buffer[k], 0, NULL, 0);
        if (result == 1) {
            strcat(buffer1, buffer[k]);
            buffer[countWritten] = strdup(buffer1);
            countWritten++;
        }
        free(buffer1);
    }
    regfree(&regex);
    free(regexstr);
    *bufferSize = countWritten;
    return buffer;
}

char** addPrefix(char** buffer, int bufferSize, char* prefix){
    for(int k = 0; k < bufferSize; k++) {
        char* buffer1 = (char*)calloc(256, sizeof(char));
        if (buffer1 == NULL) {
            perror("memory error\n");
            return NULL;
        }
	buffer1[0] = '\0';
        strcat(buffer1, prefix);
        strcat(buffer1, buffer[k]);
        strcpy(buffer[k], buffer1);
        free(buffer1);
    }
    return buffer;
}

char** addSuffix(char** buffer, int bufferSize, char* suffix){
    for(int k = 0; k < bufferSize; k++) {
        char* buffer1 = (char*)calloc(256, sizeof(char));
        if (buffer1 == NULL) {
            perror("memory error\n");
            return NULL;
        }
	buffer1[0] = '\0';
        strcat(buffer1, buffer[k]);
        strcat(buffer1, suffix);
        strcpy(buffer[k], buffer1);
        free(buffer1);
    }
    return buffer;
}
