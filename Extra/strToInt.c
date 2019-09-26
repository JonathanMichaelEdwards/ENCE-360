/*
 *  pointers.c - an exercise in memory allocation with pointers.
 *
 *  compile with: gcc pointers.c -o pointers -std=c99
 *  run with ./pointers
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>


/*
 * Convert a string to a int
 */
char *itoa(int value, char* result) 
{
    int base = 10;
    // check that the value if valid
    if (value < -32768 || value > 65536) return (char*)'\0';

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


int main()
{
    int a = -1000; 
    char *b = (char*)malloc(sizeof(a));
    printf("%s\n", itoa(a, b));
    
    
    exit(EXIT_SUCCESS);
}
