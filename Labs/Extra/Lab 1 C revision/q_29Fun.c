#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


void reallocExample()
{
    char *name = malloc(sizeof(char) * 6);  // including null terminator
    memcpy(name, "Hello", sizeof(char) * 6);

    name = realloc(name, sizeof(char) * 12);
    strcat(name, " Jono");

    puts(name);
}


typedef struct {
  char *data;
  
  size_t length;
  size_t reserved;
  
} Buffer;   


void append_buffer(Buffer *buffer, char *data, size_t length)
{
    Buffer *buff = malloc(sizeof(Buffer));
    buff->data = malloc(sizeof(char*) * buffer->length + buffer->reserved);
    memcpy(buff->data, buffer->data, sizeof(char*) * buffer->length + buffer->reserved);

    buff->data = realloc(buff->data, sizeof(char*) * length);
    strcat(buff->data, data);
    puts(buff->data);
}


int main(void)
{
    // Buffer *q = NULL;
    // append_buffer(q, NULL, 1);


    Buffer q1 = {"Hello", 7, 20};
    append_buffer(&q1, "Jono", 6);
    Buffer q2 = {"ENCE-", 7, 20};
    append_buffer(&q2, "360", 4);
    
    // reallocExample();

    return 0;
}
