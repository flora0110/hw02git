#include <stdio.h>
#include <stdlib.h>
typedef struct List* listpointer;
typedef struct List{
    int data;
    listpointer pre;
    listpointer next;
}list;
listpointer first;
int main(){
    int i;
    listpointer last,plat;
    first=(listpointer)malloc(sizeof(list));
    first->data=64;
    last=first;
    for(i=1;i<20;i++){
        plat=(listpointer)malloc(sizeof(list));
        plat->data=64;
        plat->pre=last;
        last->next=plat;
        last=plat;
    }
    first->pre=plat;
    plat->next=first;
    char control;
    while(control!='\n'){
        control=getc(stdin);
        switch (control) {
            case '+':
                first->data = ((first->data)+1)%64 +64;
                break;
            case '-':
                first->data = (first->data)-1;
                if(first->data<64){
                    first->data = first->data-64+91;
                }
                break;
            case '>':
                first=first->next;
                break;
            case '<':
                first=first->pre;
                break;
            case '.':
                if(first->data==64){
                    printf(" ");
                }
                else{
                    printf("%c ",first->data);
                }
        }
    }
}
