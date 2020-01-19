#ifndef STRING_H
#define STRING_H

#include "../cpu/types.h"


void hex_to_ascii(int n, char str[]);
void int_to_ascii(int n, char str[]);

void reverse(char s[]);

int strlen(char s[]);

void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);


char* strcpy(char* dest, char* src);


#endif
