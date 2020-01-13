void memory_copy(char* src, char* dest, int nbytes){
    int i =0; 
    while (i < nbytes)
    {
        /* code */
        *(dest + i) = *(src + i);
       i++;
    }
    
}
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
}