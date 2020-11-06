#include <stdio.h>
#include <stdlib.h>
int count=0;
typedef struct List* listpointer;
typedef struct List{
    int* data;
    listpointer link;
}list;
listpointer front=NULL,rear;

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
    if(i==n){
        if(m!=count){
            return;
        }
        addq(temp);
        //test-------------------
        int j;
        printf("________test__________\n");
        for(j=0;j<n;j++){
            printf("%d ",rear->data[j]);
        }
        printf("\n");
        //---------------------------------
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
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    int *temp=(int*)malloc(n*sizeof(int));
    dfs(temp,0,0,n,m);//把可能性弄完
    int i,j;
    int who,ans;//who 說 who ...說ans
    char c;
    listpointer now,nowtemp,last;
    int test=1;
    for(i=0;i<n;i++){//輸入敘述
        printf("narrative\n", );
        do{
            scanf("%d%c",&who,&c);
            printf("%d \n",who );
        }while(c=='>');
        ans= (c=='T') ?1:-1;
        now=front;
        last=front;
        while(now!=NULL){//刪掉不符合敘述的
            for(j=0;j<n;j++){//test
                test *= now->data[j];
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
    for(j=0;j<n;j++){
        if(front->data[j]==-1){
            printf("%d ",j );
        }
    }
}
