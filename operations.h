#pragma once

typedef struct {
    int cnum;
    char* str1;
    char* str2;
} Command;

Command command(char* str);
char** replace(char** buffer, int bufferSize, char* substr, char* newstr);
char** deleteStr(char** buffer, int* bufferSize, char* substr);
char** addPrefix(char** buffer, int bufferSize, char* prefix);
char** addSuffix(char** buffer, int bufferSize, char* suffix);
