#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"
int main(int argc,char **argv)
{
    if(argc>1)
    {
    FILE *fp;
    FILE *fc;
    fc=fopen("T20_World_Cup.txt","r");
    fp=fopen("Never_Give_Up.txt","r");
    
    if(fp==NULL)
    {
        printf("file is not there da magney\n");
        exit (1);
    }
    if(fc==NULL)
    {
        printf("file is not there da magney\n");
        exit (1);
    }
    for(int i=1;i<argc;i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    char *text;
    int capacity=1000;
    text=malloc(capacity*sizeof(char));
    text[0] = '\0';
    text=read_input(text,&capacity,argc,argv,fp);
    Result r = analyze(text);
    char *text_fc;
    int capacity_fc=1000;
    text_fc=malloc(capacity_fc*sizeof(char));
    text_fc[0] = '\0';
    text_fc=read_input(text_fc,&capacity_fc,argc,argv,fc);
    Result r_fc = analyze(text_fc);
    if(argc > 3)
    {
        if(strcmp(argv[3],"-w")==0)
        {
            printf("Words: %d\n",r.words);
        }
        else if(strcmp(argv[3],"-c")==0)
        {
            printf("Characters: %d\n",r.characters);
        }
        else if(strcmp(argv[3],"-s")==0)
        {
            printf("Sentences: %d\n",r.sentences);
        }
        else if(strcmp(argv[3],"-p")==0)
        {
            printf("Paragraphs: %d\n",r.paragraphs);
        }
        else
        {
            print_result(r);
            print_result(r_fc);
        }
    }
    else
    {
        print_result(r);
        print_result(r_fc);
    }
    
    free(text);
    free(text_fc);

    return 0;
}
else
{
    printf("Please provide a file name as an argument.\n");
    return 1;
}
}