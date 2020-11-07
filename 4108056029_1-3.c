#include <stdio.h>
#include <stdlib.h>
int count=0;
typedef struct List* listpointer;
typedef struct List{
    int* data;
    listpointer link;
}list;
listpointer front,rear;
void addq(int* item){
    listpointer temp=(listpointer)malloc(sizeof(list));
    temp->data=item;
    temp->link=NULL;
    if(!front){
        front=temp;
    }
    else{
        rear->link=temp;
    }
    rear=temp;
}
int* deleteq(){
    listpointer temp=front;
    int* item;
    if(front){
        item=front->data;
        front=temp->link;
        free(temp);
        return item;
    }
}
void dfs(int *temp,int i,int count,int n,int m){
    int j;
    if(i==n){
        if(m!=count){
            return;
        }
        int *item=(int*)malloc(n*sizeof(int));//小心指標會一起改
        for(j=0;j<n;j++){
            item[j]=temp[j];
        }
        addq(item);
        return;
    }
    temp[i]=1;

    dfs(temp,i+1,count,n,m);

    if(count!=m){//說謊的人還沒滿
        temp[i]=-1;
        dfs(temp,i+1,count+1,n,m);
    }
}
int main(){
    FILE* rptr;
    FILE* wfile;
    rptr=fopen("test1-3.txt","r");
    wfile=fopen("output1-3.txt","w");
    if(rptr==NULL || wfile==NULL){
        printf("open failure\n");
        return 1;
    }
    else{
        int n,m;
        front=NULL;
        fscanf(rptr,"%d\n",&n);
        fscanf(rptr,"%d\n",&m);
        int *temp=(int*)malloc(n*sizeof(int));
        dfs(temp,0,0,n,m);//把可能性弄完
        int i,j;
        int who,ans=1;//who 說 who ...說ans
        char c;
        //int whoin[n];
        int narr[600];
        int tatal=0;
        listpointer now,nowtemp,last;
        int test=1;
        for(i=0;i<n;i++){//輸入敘述
            for(j=0;j<tatal;j++){//歸零
                narr[j]=0;
            }
            tatal=0;
            do{
                fscanf(rptr,"%d%c",&who,&c);
                narr[tatal++]=who;
            }while(c=='>');
            fscanf(rptr,"%c",&c );
            if(c=='T'){
                ans=1;
            }
            else if(c=='L'){
                ans=-1;
            }
            else{
                printf("error\n");
                break;
            }
            now=front;
            last=front;
            while(now!=NULL){//刪掉不符合敘述的
                test=1;
                for(j=0;j<tatal;j++){//test
                    test *= now->data[narr[j]];
                }
                nowtemp=now;
                now=now->link;
                if(test!=ans){
                    if(nowtemp==front){//現在是front用deleteq
                        deleteq();
                    }
                    else{
                        last->link=nowtemp->link;
                        free(nowtemp);
                    }
                }
                else{
                    last=nowtemp;//更新上一點
                }
            }//-----------------
        }
        printf("output:");
        fprintf(wfile,"output:");
        for(j=0;j<n;j++){
            if(front->data[j]==-1){
                printf("%d ",j );
                fprintf(wfile,"%d ",j );
            }
        }
    }
}
