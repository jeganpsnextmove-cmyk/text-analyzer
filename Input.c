#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"
char *read_input(char *text, int *capacity,int argc,char **argv,FILE *fp)
{
    char line[100];
    int length = 0;
    int line_length;
    

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
    fclose(fp);
    return text;
}