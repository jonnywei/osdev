#include "string.h"


/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */

        reverse(str);
}

// void reverse(char s[]){
//     int last = strlen(s)-1;
//     int i= 0;
//     char temp ;
//     while(i <= last/2){
//         temp = s[i];
//         s[i] = s[last-i] ;
//         s[last-1] = temp;
//         i++;
//     }
// }

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]){
    int len = 0;
    while(s[len] != '\0'){ len++;};
    return len;
}


void backspace(char s[]){
     int len = strlen(s);
     s[len-1] = '\0';
}
void append(char s[], char n){

     int len = strlen(s);
     s[len] = n;
     s[len+1] ='\0';

}
int strcmp(char s1[], char s2[]){
    int i;
    for( i=0; s1[i] == s2[i]; i++){
         if (s1[i] == '\0') return 0;
    }
    return s1[i] -s2[i];
}

