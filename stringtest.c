#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char str[100];
    int i;
    int n;
    for(i=0;i<1;i++){

    }
    char c;
    scanf("%[1234567890nul]",str);
    printf("1.  %s %d\n",str,strlen(str));
    //memset(str,'\0',strlen(str));
    printf("%d\n",strlen(str));
    //scanf("%d",&n);
    //printf("%d\n",n );
    c=getc(stdin);
    printf("%c\n",c );
    //fflush(stdin);
    scanf("%[^,]",str);
    printf("2.  %s %d\n",str,strlen(str));
    fflush(stdin);
    scanf("%[1234567890nul]",str);
    printf("3.  %s %d\n",str,strlen(str));
}
