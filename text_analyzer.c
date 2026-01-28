#include<stdio.h>
#include<string.h>
typedef struct
{
    int characters;
    int words;
    int sentences;
    int paragraphs;
} Result;

void read_input(char text[], int size)
{
    char line[200];

    printf("Text Analyzer Tool v1\n");
    printf("Enter text (Ctrl+D to stop):\n\n");

    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        strcat(text, line);
    }
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

        if (ch != ' ' && ch != '\n' && ch != '.')
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
        else if (ch == '.')
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

            if (sentence_has_word)
            {
                r.sentences++;
                sentence_has_word = 0;
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
    char text[2000] = "";

    read_input(text, sizeof(text));

    Result r = analyze(text);

    print_result(r);

    return 0;
}