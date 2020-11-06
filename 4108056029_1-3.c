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
/*void testprintf(listpointer x,int n){
     int k=0;
    while(x){
        int i;
        printf("list %d\n",k++);
        for(i=0;i<n;i++){
            printf("%d \n",x->data[i]);
        }
        printf("\n");
        x=x->link;
    }
}*/
int main(){
    int n,m;
    front=NULL;
    scanf("%d",&n);
    scanf("%d",&m);
    int *temp=(int*)malloc(n*sizeof(int));
    dfs(temp,0,0,n,m);//把可能性弄完
    /*printf("-------------test------------\n");
    testprintf(front,n);
    printf("-----------------------------\n");*/
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
        //printf("narrative : %d\n",i);
        tatal=0;
        do{
            //printf("read..\n");
            scanf("%d%c",&who,&c);
            //whoin[who]=1;//這次有在敘述中
            narr[tatal++]=who;
            //printf("%d \n",who );
        }while(c=='>');
        scanf("%c",&c );
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
        //ans = (c=='T') 1:-1;
        //printf("ans=%d\n",ans);
        now=front;
        last=front;
        while(now!=NULL){//刪掉不符合敘述的
            /*printf("start to delete-------------------\n");
            printf("-------------test------------\n");
            testprintf(front,n);
            printf("-----------------------------\n");*/
            test=1;
            /*for(j=0;j<n;j++){//test
                if(whoin[j]){
                    test *= now->data[j];
                }
            }*/
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
            /*printf("-------------after delete test------------\n");
            testprintf(front,n);
            printf("-----------------------------\n");*/
        }//-----------------
    }
    printf("output:");
    for(j=0;j<n;j++){
        if(front->data[j]==-1){
            printf("%d ",j );
        }
    }
}
