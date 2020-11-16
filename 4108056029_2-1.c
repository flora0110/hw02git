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
    FILE* rptr;
    FILE* wfile;
    rptr=fopen("test2-1.txt","r");//testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest
    wfile=fopen("output2-1.txt","w");
    if(rptr==NULL || wfile==NULL){
        printf("open failure\n");
        return 1;
    }
    else{
        char control;
        control=fgetc(rptr);
        while(control!='\n' && control!=EOF){
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
                        fprintf(wfile," ");
                    }
                    else{
                        printf("%c",first->data);
                        fprintf(wfile,"%c",first->data);
                    }
            }
            control=fgetc(rptr);
        }
    }
    fclose(wfile);
    fclose(rptr);
}
