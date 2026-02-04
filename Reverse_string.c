#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char * rev_string(char *arr)
{
    int i,j;
    char temp;
    int len;
    len=strlen(arr);
    for(i=0,j=len-1;i<j;i++,j--)
    {
        temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    return arr;
}

int main()
{
    char * arr;
    int capacity;
    printf("Enter the capacity of the string: ");
    scanf("%d", &capacity);
        getchar();  // Clear newline from scanf
    arr=calloc(capacity+1, sizeof(char));
   
    fgets(arr, capacity+1, stdin);
    rev_string(arr);
    for(int i=0;arr[i]!='\0';i++)
    {
        printf("%c",arr[i]);
    }
    free(arr);
    return 0;
}