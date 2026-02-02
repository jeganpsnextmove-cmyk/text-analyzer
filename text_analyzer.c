#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
    int characters;
    int words;
    int sentences;
    int paragraphs;
    char longest_word[100];
    int char_max_count;
} Result;

char *read_input(char *text, int *capacity,int argc,char **argv,FILE *fp)
{
    char line[100];
    int length = 0;
    int line_length;
    printf("Text Analyzer Tool v1\n");
    printf("Enter text (Ctrl+D to stop):\n\n");

    while (fgets(line, sizeof(line), fp))
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
    fclose(fp);
    return text;
}

Result analyze(char text[])
{
    Result r = {0, 0, 0, 0};
    int inside_word = 0;
    int sentence_has_word = 0;
    int line_has_word = 0;
    char long_word[100];
    char longest_word[100];
    int char_max_count=0;
    int char_count=0;
     
    for (int i = 0; text[i] != '\0'; i++)
    {
        char ch = text[i];

        if (ch != ' ' && ch != '\n' && ch != '.' && ch != '?' && ch != '!')
        {
            r.characters++;
            long_word[char_count]=ch;
            char_count++;
            if (!inside_word)
            {
                inside_word = 1;
                sentence_has_word = 1;
                line_has_word = 1;
            }
        }
        else if (ch == ' ')
        {
            if(r.char_max_count<char_count)
            {
                r.char_max_count=char_count;
                long_word[char_count]='\0';
                strcpy(r.longest_word,long_word);
            }
            if (inside_word)
            {
                r.words++;
                inside_word = 0;
            }
            char_count=0;
        }
        else if (ch == '.' || ch == '?' || ch == '!')
        {
            if(r.char_max_count< char_count)
            {
                r.char_max_count=char_count;
                long_word[char_count]='\0';
                strcpy(r.longest_word,long_word);
            }
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
            char_count=0;
        }
        else if (ch == '\n')
        {
            if(r.char_max_count<char_count)
            {
                r.char_max_count=char_count;
                long_word[char_count]='\0';
                strcpy(r.longest_word,long_word);
            }
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
            char_count=0;
        }
    }
    if(r.char_max_count<char_count)
    {
        r.char_max_count=char_count;
        long_word[char_count]='\0';
        strcpy(r.longest_word,long_word);
    }
    
     printf("Longest word: %s (Length: %d)\n",r.longest_word,r.char_max_count);

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


int main(int argc,char **argv)
{
    FILE *fp;
    fp=fopen("T20_World_cup.txt","r");
    if(fp==NULL)
    {
        printf("file is not there da magney\n");
        exit (1);
    }
    for(int i=1;i<argc;i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    char *text ;
    int capacity=1000;
    text=malloc(capacity*sizeof(char));
    text[0] = '\0';

    text=read_input(text, &capacity,argc,argv,fp);


    Result r = analyze(text);

    print_result(r);
    
    free(text);

    return 0;
}