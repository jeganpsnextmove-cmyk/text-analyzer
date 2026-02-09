#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>

typedef struct
{
    int characters;
    int words;
    int sentences;
    int paragraphs;
    char longest_word[100];
    int char_max_count;
} Result;

char *read_input(char *text, int *capacity, int argc, char **argv, FILE *fp);
Result analyze(char text[]);
void print_result(Result r);

#endif