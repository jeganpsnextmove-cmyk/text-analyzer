#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
    int characters;
    int words;
    int sentences;
    int paragraphs;
} Result;

char *read_input(char *text, int *capacity)
{
    char line[100];
    int length = 0;
    int line_length;
    printf("Text Analyzer Tool v1\n");
    printf("Enter text (Ctrl+D to stop):\n\n");

    while (fgets(line, sizeof(line), stdin) )
{
        line_length=strlen(line);
        while(length + line_length + 1 > *capacity)
        {
            *capacity *= 2;
            char * temp = realloc(text, *capacity);
            if (temp == NULL)
            {
                printf("Memory allocation failed\n");
                exit(1);
            }
            text = temp;
        }
        strcpy(text + length, line);
        length += line_length;
    }
    text[length]= '\0';
    return text;
}

Result analyze(char text[])
{
    Result r = {0, 0, 0, 0};

    int inside_word = 0;
    int sentence_has_word = 0;
    int line_has_word = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];

        if (ch != ' ' && ch != '\n' && ch != '.' && ch != '?' && ch != '!')
        {
            r.characters++;

            if (!inside_word)
            {
                inside_word = 1;
                sentence_has_word = 1;
                line_has_word = 1;
            }
        }
        else if (ch == ' ')
        {
            if (inside_word)
            {
                r.words++;
                inside_word = 0;
            }
        }
        else if (ch == '.' || ch == '?' || ch == '!')
        {
            if (inside_word)
            {
                r.words++;
                inside_word = 0;
            }

            if (sentence_has_word)
            {
                r.sentences++;
                sentence_has_word = 0;
            }
        }
        else if (ch == '\n')
        {
            if (inside_word)
            {
                r.words++;
                inside_word = 0;
            }

            if (line_has_word == 0)
            {
                r.paragraphs++;
            }

            line_has_word = 0;
        }
    }

    if (inside_word)
        r.words++;

    if (sentence_has_word)
        r.sentences++;

    if (r.words > 0)
        r.paragraphs++;

    return r;
}
void print_result(Result r)
{
    printf("\n--- Analysis Result ---\n");
    printf("Characters : %d\n", r.characters);
    printf("Words      : %d\n", r.words);
    printf("Sentences  : %d\n", r.sentences);
    printf("Paragraphs : %d\n", r.paragraphs);
    printf("------------------------\n");
}


int main()
{
    char *text ;
    int capacity=1000;
    text=malloc(capacity*sizeof(char));
    text[0] = '\0';

    text=read_input(text, &capacity);


    Result r = analyze(text);

    print_result(r);
    
    free(text);

    return 0;
}