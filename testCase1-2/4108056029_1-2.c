#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        printf("out\n");\
        exit(EXIT_FAILURE);\
    }
#define MAX_QUEUES 15000
struct TreeNode {
     int data;
     struct TreeNode* left;
     struct TreeNode* right;
};
typedef struct TreeNode node;
//存樹的queue
typedef struct queue* queuepointer;
typedef struct queue{
    node* nodelink;
    queuepointer link;
}queue;
queuepointer front=NULL,rear;

node* queueEmpty(){
    printf("queue is empty\n");
    node* item;
    item->data=-1;
    item->left=NULL;
    item->right=NULL;
    return item;
}
void addq(node* item){
    queuepointer temp;
    temp=(queuepointer)malloc(sizeof(queue));
    temp->nodelink=item;
    temp->link=NULL;
    if(front){
        rear->link=temp;
    }
    else
        front=temp;
    rear=temp;
    if(front==NULL){
        printf("front is null\n");
    }
}

node* deleteq(){
    queuepointer temp=front;
    node* item;
    if(!temp){
        return queueEmpty();
    }
    item = temp->nodelink;
    front=temp->link;
    free(temp);
    return item;
}
//---------------存樹的queue--------------------------


typedef struct imfor{
    int data;//節點裡的值
    int mark;//標記
    int *zip;
}imfor;

int numarray[15000];//存堡壘
//int minnum[15000];
int sum=0;//堡壘cost
int count=0;//堡壘數(控制numarray)
//int mincount;
int checkn=0;//需要check 的點
node *root;
void rezip(int* zip){
    //printf("in zip\n");
    if(zip[1]>=0){
        numarray[count++]=zip[1];
    }
    else{
        zip[1]=0;
    }
    if(zip[2]>=0){
        numarray[count++]=zip[2];
    }
    else{
        zip[2]=0;
    }
}
imfor find (node* ptr,node* fatherptr){
    int i;
    //printf("in find\n");
    imfor nowimfor;
    if(ptr==NULL){
        //printf("null\n");
        nowimfor.data=0;
        nowimfor.mark=-1;
        return nowimfor;
    }
    //printf("------------ptr->data %d\n",ptr->data);
    nowimfor.data=ptr->data;
    nowimfor.mark=0;
    int fatherdata=fatherptr->data;
    imfor leftimfor=find(ptr->left,ptr);
    imfor rightimfor=find(ptr->right,ptr);
    int rightdata=rightimfor.data;
    int rightmark=rightimfor.mark;
    int leftdata=leftimfor.data;
    int leftmark=leftimfor.mark;
    if(leftmark==-1 && rightmark==-1){
        nowimfor.mark=-2;
        //printf("%d is x\n",ptr->data );
        return nowimfor;
    }
    //-5-4
    if((leftmark==-5 && rightmark==-4) || (leftmark==-4 && rightmark==-5)){
        //printf("%d in -5 -4\n",ptr->data);
        nowimfor.mark=-1;
        nowimfor.data=0;
        //不標-5點
        if(leftmark==-5){
            //printf("left\n" );
            rezip(leftimfor.zip);
            sum+=leftimfor.zip[1]+leftimfor.zip[2];
        }
        if(rightmark==-5){
            //printf("in\n");
            rezip(rightimfor.zip);
            //printf("out zip\n");
            //numarray[count++]=rightimfor.zip[1];
            //numarray[count++]=rightimfor.zip[2];
            sum+=rightimfor.zip[1]+rightimfor.zip[2];
        }
        return nowimfor;
    }
    if((leftmark==-4 && rightmark==-1) || (leftmark==-1 && rightmark==-4)){
        //printf("%d in -1 -4\n",ptr->data);
        nowimfor.mark=-1;
        nowimfor.data=0;
        return nowimfor;
    }
    //-5-1
    if((leftmark==-5 && rightmark==-1) || (leftmark==-1 && rightmark==-5)){
        //printf("%d in -5 -1\n",ptr->data);
        nowimfor.mark=-2;
        //不標-5點
        if(leftmark==-5){
            rezip(leftimfor.zip);
            sum+=leftimfor.zip[1]+leftimfor.zip[2];
            //printf("%d %d\n",leftimfor.zip[1],leftimfor.zip[2]);
        }
        if(rightmark==-5){
            rezip(rightimfor.zip);
            //printf("out zip\n");
            sum+=rightimfor.zip[1]+rightimfor.zip[2];
            //printf("%d %d\n",rightimfor.zip[1],rightimfor.zip[2]);
            //printf("out zip\n");
        }
        return nowimfor;
    }
    //-5-2
    if(leftmark==-5 && rightmark==-2){//等等還要經過-3處理
        //printf("%d in -5 -2\n",ptr->data);
        leftmark=-1;
        leftdata=0;
        //不標-5點
        rezip(leftimfor.zip);
            sum+=leftimfor.zip[1]+leftimfor.zip[2];
            //printf("%d %d\n",leftimfor.zip[1],leftimfor.zip[2]);
    }
    if(leftmark==-2 && rightmark==-5){
        //printf("%d in -5 -2\n",ptr->data);
        rightmark=-1;
        rightdata=0;
        //不標-5點
        rezip(rightimfor.zip);
            //printf("%d %d\n",rightimfor.zip[1],rightimfor.zip[2]);
            sum+=rightimfor.zip[1]+rightimfor.zip[2];
    }

    if((leftmark==-2 || rightmark==-2)){
        nowimfor.mark=-3;
        if(ptr->data<(rightdata+leftdata)){
        //printf("%d in -4\n",ptr->data);
            nowimfor.mark=-4;
            numarray[count++]=ptr->data;
            sum+=ptr->data;
        }
        else if(ptr->data>(rightdata+leftdata)){
            //printf("%d in -5\n",ptr->data);
            if(ptr==root){
                if(leftmark==-2){
                    numarray[count++]=leftdata;
                }
                else{
                    leftdata=0;
                }
                if(rightmark==-2){
                    numarray[count++]=rightdata;
                }
                else{
                    rightdata=0;
                }
                sum+=(leftdata+rightdata);
            }
            MALLOC(nowimfor.zip,3*sizeof(int));
            nowimfor.mark=-5;
            nowimfor.zip[0]=ptr->data;
            if(leftmark==-2){
                nowimfor.zip[1]=leftdata;
            }
            else{
                nowimfor.zip[1]=-1;
            }
            if(rightmark==-2){
                nowimfor.zip[2]=rightdata;
            }
            else{
                nowimfor.zip[2]=-1;
            }
            nowimfor.data=ptr->data-(rightdata+leftdata);

        }

    }
    if(leftmark==-5 && rightmark==-5 ){
        //printf("%d in -5 -5\n",ptr->data);
        if(ptr==root){
            if(ptr->data<leftdata && ptr->data<rightdata){
                nowimfor.mark=-4;
                numarray[count++]=ptr->data;
                sum+=ptr->data;
                rezip(leftimfor.zip);
                //printf("left %d %d\n",leftimfor.zip[1],leftimfor.zip[2]);
                sum+=leftimfor.zip[1]+leftimfor.zip[2];

                rezip(rightimfor.zip);
                sum+=rightimfor.zip[1]+rightimfor.zip[2];
                //printf("right %d %d\n",rightimfor.zip[1],rightimfor.zip[2]);
                return nowimfor;
            }
            else{
                if(rightdata>leftdata){
                    nowimfor.mark=-4;
                    numarray[count++]=leftimfor.zip[0];
                    sum+=leftimfor.zip[0];
                    //printf("left %d\n",leftimfor.zip[0]);
                    rezip(rightimfor.zip);
                    //printf("right %d %d\n",rightimfor.zip[1],rightimfor.zip[2]);
                    sum+=rightimfor.zip[1]+rightimfor.zip[2];
                }
                else{
                    nowimfor.mark=-4;
                    numarray[count++]=rightimfor.zip[0];
                    sum+=rightimfor.zip[0];
                    //printf("right %d\n",rightimfor.zip[0]);
                    rezip(leftimfor.zip);
                    //printf("left %d %d\n",leftimfor.zip[1],leftimfor.zip[2]);
                    sum+=leftimfor.zip[1]+leftimfor.zip[2];
                }
            }
        }
        else{
            //nowimfor.mark=-7;
            //MALLOC(nowimfor.tozip,2*sizeof(int*));
            //nowimfor.tozip[0]=leftimfor.zip;
            //nowimfor.tozip[1]=rightimfor.zip;
            //printf("%d in min\n",ptr->data);
            int minnode;
            if(ptr->data<=leftdata && ptr->data<=rightdata){
                minnode=ptr->data;
                nowimfor.mark=-2;
                rezip(rightimfor.zip);
                sum+=rightimfor.zip[1]+rightimfor.zip[2];
                rezip(leftimfor.zip);
                sum+=leftimfor.zip[1]+leftimfor.zip[2];
            }
            else if(leftdata<=ptr->data && leftdata<=rightdata){
                minnode=leftdata;
                nowimfor.mark=-5;
                nowimfor.zip=leftimfor.zip;
                rezip(rightimfor.zip);
                sum+=rightimfor.zip[1]+rightimfor.zip[2];
            }
            else{
                minnode=rightdata;
                nowimfor.mark=-5;
                nowimfor.zip=rightimfor.zip;
                rezip(leftimfor.zip);
                sum+=leftimfor.zip[1]+leftimfor.zip[2];
            }
            nowimfor.data=minnode;
        }
    }
    //printf("finish------------ptr->data %d %d\n",ptr->data,nowimfor.mark);
    return nowimfor;
}
//--------------------------可能性
int testn=0;
node *root;
void postorder(node* ptr){
    if(ptr){
        printf("%d\n",ptr->data);
        postorder(ptr->left);
        postorder(ptr->right);
    }
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test5.txt","r");//testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest
    if(rptr==NULL){
        printf("ERROR\n");
        return 0;
    }
    else{
        int i,j;
        char c;
        //node* root;
        root=NULL;
        c=fgetc(rptr);
        char str[100];
        //int n=0;
        int num;
        if(c=='['){//開始建立樹
            //c=fgetc(rptr);//抓根
            fscanf(rptr,"%[1234567890nul]",str);
            //printf("%s\n",str);
            if(strncmp("null",str,4)!=0){
                num=atoi(str);
                //memset(str,'\0',strlen(str));
                root=(node*)malloc(sizeof(node));
                c=fgetc(rptr);
                root->data=num;
                addq(root);
                //n++;
            }
            /*if(c!=n){
                root=(node*)malloc(sizeof(node));
                c=fgetc(rptr);
                root->data=0;
                addq(root);
                n++;
            }*/
            while(front){
                struct TreeNode* current;//現在在幫誰加葉子
                current=deleteq();
                if(c==']'){//結束
                    break;
                }
                //c=fgetc(rptr);
                fscanf(rptr,"%[1234567890nul]",str);
                //printf("%s\n",str);
                if(strncmp("null",str,4)!=0){
                    num=atoi(str);
                    node* newnode;
                    newnode=(node*)malloc(sizeof(node));
                    current->left=newnode;
                    newnode->data=num;
                    newnode->left=NULL;
                    newnode->right=NULL;
                    addq(newnode);
                    //n++;
                }
                else{
                    current->left=NULL;
                    //fscanf(rptr,"%*[ull]");//吃掉ull
                }
                c=fgetc(rptr);//吃','
                if(c==']'){
                    break;
                }
                fscanf(rptr,"%[1234567890nul]",str);
                //printf("%s\n",str);
                //c=fgetc(rptr);
                if(strncmp("null",str,4)!=0){
                    num=atoi(str);
                    node* newnode;
                    newnode=(node*)malloc(sizeof(node));
                    current->right=newnode;
                    newnode->left=NULL;
                    newnode->right=NULL;
                    newnode->data=num;
                    //newnode->n=test++;
                    addq(newnode);
                    //n++;
                }
                else{
                    current->right=NULL;
                    //fscanf(rptr,"%*[ull]");
                }
                c=fgetc(rptr);//eat ','or']'
            }//-----------------------------------------------完成樹
        }
        else{//輸入非以[開頭
            printf("input error\n");
        }
        if(root!=NULL){
            //postorder(root);
            count=0;
            imfor check=find(root,NULL);
            if(check.mark==-2){
                sum+=check.data;
                numarray[count++]=check.data;
            }
        }
        printf("output: %d(",sum);
        for(i=0;i<count-1;i++){
            printf("%d +",numarray[i]);
        }
        printf("%d)\n",numarray[count-1]);
    }
}
