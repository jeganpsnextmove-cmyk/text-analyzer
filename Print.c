#include"header.h"
void print_result(Result r)
{
    printf("\n--- Analysis Result ---\n");
    printf("Characters : %d\n", r.characters);
    printf("Words      : %d\n", r.words);
    printf("Sentences  : %d\n", r.sentences);
    printf("Paragraphs : %d\n", r.paragraphs);
    printf("------------------------\n");
}