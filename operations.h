#pragma once

typedef struct {
    int cnum;
    char* str1;
    char* str2;
} Command;

Command command(char* str);
char* replace(char* buffer, char* substr, char* newstr);
char* deleteStr(char* buffer, char* substr);
char* addPrefix(char* buffer, char* newstr);
char* addSuffix(char* buffer, char* newstr);
