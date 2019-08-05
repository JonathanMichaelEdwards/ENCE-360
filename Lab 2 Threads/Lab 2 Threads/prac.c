#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Declare the StringPair type.
// Note that we have incorporated the struct declaration into
// the typedef, but that this only works because we don't have any
// StringPair pointers in the structure (e.g. StringPair* next).
typedef struct stringpair_s {
    char* first;
    char* second;
 } StringPair;



StringPair* newStringPair(const char *s1, const char *s2)
{
    StringPair *pair = malloc(strlen(s1) + strlen(s2));
    pair->first = malloc(strlen(s1));
    pair->second = malloc(strlen(s2));
    strcpy(pair->first, s1);
    strcpy(pair->second, s2);

    return pair;
}



int main(void)
{
    char s1[] = "My first string";
    char s2[] = "Another one";
    StringPair* pair = NULL;

    pair = newStringPair(s1, s2);

    // Before printing, alter the initial strings to ensure
    // the function hasn't just copied the pointers.
    strncpy(s1, "Smasher1", sizeof(s1));
    strncpy(s2, "Clobber2", sizeof(s2));

    // Now print the new StringPair.
    printf("String pair: ('%s', '%s')\n", pair->first, pair->second);

    // Lastly free all dynamic memory involved.
    free(pair->first);
    free(pair->second);
    free(pair);
}
