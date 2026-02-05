#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    printf("Enter the strings:\n");
    fgets(str,sizeof(str),stdin);
      int len=strlen(str);
   if (str[len-1]== '\n') 
    {
        str[len-1] = '\0';
        len--;
    }
  
    int end=len-1;
    char sentence[100];
    printf("Reversed words: ");  
    for(int i=len-1;i>=0;i--)
    {
        if(i==0 || str[i]==' ')
        {
            int start;
            if(i==0)
                start=0;
            else
                start=i+1;
            for(int j=start;j<=end;j++)
            {        
                       
        printf("%c",str[j]);
            }
            printf(" ");
            end=i-1;
        }
    }
    return 0;
}