#include<string.h>
#include"header.h"
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
