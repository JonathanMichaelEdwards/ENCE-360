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
#include <assert.h>
#include <malloc.h>



void concatMessage()
{
    char *message1 = "Hello";
    char *message2 = " Jonathan";

    char *name = malloc(sizeof(char) * strlen(message1));  // initial
    memcpy(name, message1, 5);  // copy the first message

    name = realloc(name, sizeof(char) * 16);

    memcpy(&name[5], message2, 9);  // concaternate the second message with the first

    puts(name);
}


// Concaternating extra characters by reallocating memory
void addOn(const char *message_1, const char *message_2, char *text)
{
    text = (char*)realloc(text, sizeof(char) * (strlen(message_1)+strlen(message_2)+1));

    for (int i = 0; i < strlen(message_2); i++)
        text[strlen(message_1)+i] = message_2[i];
}


// note: Use this when 'NOT' using threads
// Passing a single pointer into a function
void singlePoninter(const char *message, char *text)
{
    const char *type = "from the SINGLE pointer.";

    for (int i = 0; i < strlen(message); i++) 
        text[i] = message[i];
    
    addOn(message, type, text);  // Adding extra text
}


// note: Use this when 'USING' threads
// Using the reference of the single pointer for the double pointer
void doublePoninter(const char *message, char **cpyText)
{
    const char *type = "from the DOUBLE pointer.";
    char *text = (char*)malloc(sizeof(char) * strlen(message)+1);
    
    for (int i = 0; i < strlen(message); i++) 
        text[i] = message[i];
    
    addOn(message, type, text);  // Adding extra text
    *cpyText = text;             // Pointing the double pointer to the text
}


void singleInt(const int num, int *value)
{
    *value = num;
}

void doubleInt(const int num, int **value)
{
    *value = (int*)&num;
}

char *initPtr(const char *message)
{
    char *me = (char*)malloc(sizeof(char) * strlen(message)+1);
    return me;
}

int main()
{
    const char *message = "Hello ";
    const int luckyNumber = 6;

    char *cpyText_1 = initPtr(message);
    char *cpyText_2 = NULL;
    int value = 0;
    int *value_2 = 0;
    int _value_2 = 0;

    // string pointers
    singlePoninter(message, cpyText_1);
    doublePoninter(message, &cpyText_2);  // reference of the first pointer

    // int pointers
    singleInt(luckyNumber, &value);
    doubleInt(luckyNumber, &value_2);
    _value_2 = *value_2;
    concatMessage();  

    puts(cpyText_1);
    puts(cpyText_2);
    printf("The Value of the SINGLE Pointer '%d' should be %d\n", value, luckyNumber);
    printf("The Value of the DOUBLE Pointer '%d' should be %d\n", _value_2, luckyNumber);
    
    exit(0);
}
