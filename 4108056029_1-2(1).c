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

typedef struct element{
    node* nodepointer;
    int way;
}element;
typedef struct queue2* queuepointer2;
typedef struct queue2{
    element e;
    queuepointer2 link;
}queue2;
queuepointer2 front2=NULL,rear2;

element queueEmpty2(){
    printf("queue is empty\n");
    element e;
    e.nodepointer=NULL;
    e.way=0;
    return e;
}
void addq2(element item){
    queuepointer2 temp;
    temp=(queuepointer2)malloc(sizeof(queue2));
    temp->e=item;
    temp->link=NULL;
    if(front2){
        rear2->link=temp;
    }
    else
        front2=temp;
    rear2=temp;
    if(front2==NULL){
        printf("front is null\n");
    }
}

element deleteq2(){
    queuepointer2 temp=front2;
    element item;
    if(!temp){
        return queueEmpty2();
    }
    item = temp->e;
    front2=temp->link;
    free(temp);
    return item;
}
/*
typedef struct List* listpointer;
typedef struct List{
    int* data;
    listpointer link;
}list;
listpointer front3=NULL,rear3;
void addq3(int* item){
    listpointer temp=(listpointer)malloc(sizeof(list));
    temp->data=item;
    temp->link=NULL;
    if(!front3){
        front3=temp;
    }
    else{
        rear3->link=temp;
    }
    rear3=temp;
}
int* deleteq3(){
    listpointer temp=front3;
    int* item;
    if(front3){
        item=front3->data;
        front3=temp->link;
        free(temp);
        return item;
    }
}*/

typedef struct imfor{
    int data;//節點裡的值
    int mark;//標記
}imfor;
int min;
int numarray[15000];
int minnum[15000];
int sum=0;
int count=0;
int mincount;
int checkn=0;//需要check 的點
queuepointer2 top;
imfor find (node* ptr,int fatherdata,int firsttime){
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
    imfor leftimfor=find(ptr->left,ptr->data,firsttime);
    imfor rightimfor=find(ptr->right,ptr->data,firsttime);
    int rightdata=rightimfor.data;
    int rightmark=rightimfor.mark;
    int leftdata=leftimfor.data;
    int leftmark=leftimfor.mark;
    //printf("ptr->data %d leftmark: %d    rightmark: %d\n",ptr->data,leftmark,rightmark );
    if(leftmark==-4){
        nowimfor.mark=-6;
        leftmark=-1;
        leftdata=0;
    }
    if(rightmark==-4){
        nowimfor.mark=-6;
        rightmark=-1;
        rightdata=0;
    }
    if(leftmark==-5 || leftmark==-6){
        leftmark=-1;
        leftdata=0;
    }
    if(rightmark==-5 || rightmark==-6){
        rightmark=-1;
        rightdata=0;
    }
    //printf("\nnowmark %d\n",nowimfor.mark );
    //printf("leftmark: %d    rightmark: %d\n",leftmark,rightmark );
    if(leftmark==-1 && rightmark==-1 && nowimfor.mark!=-6){
        //printf("-------------------%d is x\n",ptr->data);
        nowimfor.mark=-2;
    }
    else if(leftmark==-2 || rightmark==-2){
        if(ptr->data<(rightdata+leftdata)){
            //printf("------------------------%d is case -4\n",ptr->data);
            nowimfor.mark=-4;
            numarray[count++]=ptr->data;
            sum+=ptr->data;
            //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
        }
        else if(ptr->data>(rightdata+leftdata+fatherdata)){
            //printf("------------------------%d is case -5\n",ptr->data);
            if(leftmark==-2){
                sum+=leftdata;
                //printf("count %d\n",count );
                numarray[count++]=leftdata;
                //printf("left %d\n",leftdata );
                //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
            }
            if(rightmark==-2){
                sum+=rightdata;
                //printf("count %d\n",count);
                numarray[count++]=rightdata;
                //printf("right %d\n",rightdata);
                //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
            }
            //printf("sum: %d\n",sum );
            nowimfor.mark=-5;
        }
        else{
            //printf("else\n");
            int way=1;
            if(firsttime){
                element e;
                e.nodepointer=ptr;
                e.way=1;
                addq2(e);
                checkn++;
            }
            else{
                //queuepointer2 qp=front2;
                //while (qp) {
                    if(top->e.nodepointer==ptr){
                        way=top->e.way;
                        top=top->link;
                        //break;
                    }
                    //qp=qp->link;
                //}
            }
            if(way==1){
                //printf("\nway 1\n");
                //printf("-------------------%d is case -4\n",ptr->data);
                //printf("count %d\n",count);
                nowimfor.mark=-4;
                numarray[count++]=ptr->data;
                sum+=ptr->data;
                //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
            }
            else if(way==2){
                //printf("\nway 2\n");
                //printf("-------------------%d is case -5\n",ptr->data);
                if(leftmark==-2){
                    //printf("inright\n");
                    sum+=leftdata;
                    numarray[count++]=leftdata;
                    //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
                }
                if(rightmark==-2){
                    //printf("inleft\n");
                    sum+=rightdata;
                    numarray[count++]=rightdata;
                    //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
                }
                nowimfor.mark=-5;
            }
        }
    }
    //printf("finish------------ptr->data %d %d\n",ptr->data,nowimfor.mark);
    return nowimfor;
}
//--------------------------可能性
int testn=0;
node *root;
void dfs(int *temp,int i){
    int j;
    if(i==checkn){
        //int *item;
        //int *item=(int*)malloc(checkn*sizeof(int));//小心指標會一起改
        //MALLOC(item,checkn*sizeof(int));
        /*for(j=0;j<checkn;j++){
            item[j]=temp[j];
        }*/
        //addq3(item);
        testn++;
        //printf("%d\n",testn );
        //-----------------------------------
        count=0;
        sum=0;
        queuepointer2 nptr=front2;
        for(i=0;i<checkn;i++){
            nptr->e.way=temp[i];
            nptr=nptr->link;
        }
        top=front2;
        imfor rootim = find(root,0,0);
        //printf("rootim %d\n",rootim.mark );
        if(rootim.mark==-2 ){
            printf("\n");
            numarray[count++]=root->data;
            sum+=root->data;
        }
        /*printf("-----------numarray----------######################\n");
        for(i=0;i<count;i++){
            printf("%d \n",numarray[i]);
        }
        printf("---------------------------\n");*/
        if(sum<min){
            for(i=0;i<count;i++){
                minnum[i]=numarray[i];
            }
            min=sum;
            mincount=count;
        }
        //----------------------------------
        return;
    }
    temp[i]=1;
    dfs(temp,i+1);
    temp[i]=2;
    dfs(temp,i+1);
}

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
    rptr=fopen("test4.txt","r");
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
            printf("%s\n",str);
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
            printf("----------test-----------\n");
            //postorder(root);
            //printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
            imfor rootim =find(root,0,1);//第一次
            printf("checkn %d\n",checkn );//需要檢查的點
            if(rootim.mark==-2 ){
                numarray[count++]=root->data;
                sum+=root->data;
                printf("numarray[%d] %d\n",count-1, numarray[count-1]);
            }

            min=sum;//初始化min
            for(i=0;i<count;i++){
                minnum[i]=numarray[i];
            }
            mincount=count;
            printf("-----------minnum----------######################\n");
            for(i=0;i<mincount;i++){
                printf("%d \n",minnum[i]);
            }
            printf("---------------------------\n");

            int *temp=(int*)malloc(count*sizeof(int));
            if(front2){//queue2存要處理的點
                dfs(temp,0);//把可能性弄完
            }
            printf("$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%testn %d checkn %d\n",testn,checkn );
            //dfs(temp,0);//把可能性弄完
            //int *check;//
            /*
            while(front3){
                //printf("in while\n");
                count=0;
                check=deleteq3();
                sum=0;
                queuepointer2 nptr=front2;
                for(i=0;i<checkn;i++){
                    nptr->e.way=check[i];
                    nptr=nptr->link;
                }
                top=front2;
                rootim = find(root,0,0);
                //printf("rootim.mark %d\n",rootim.mark);
                //printf("root data %d\n",root->data );
                if(rootim.mark==-2 ){
                    numarray[count++]=root->data;
                    sum+=root->data;
                    //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
                }
                //printf("-----------numarray----------######################\n");
                //for(i=0;i<count;i++){
                //    printf("%d \n",numarray[i]);
                //}
                //printf("---------------------------\n");
                if(sum<min){
                    //memcpy(minnum,numarray,sizeof(num));
                    for(i=0;i<count;i++){
                        minnum[i]=numarray[i];
                        //printf("%d \n",minnum[i]);
                    }
                    min=sum;
                    mincount=count;
                    //printf("-----------minnum----------######################\n");
                    //for(i=0;i<mincount;i++){
                    //    printf("%d \n",minnum[i]);
                    //}
                    //printf("---------------------------\n");
                }
            }
            */
        }
        printf("output: %d\n",min);
        for(i=0;i<mincount;i++){
            printf("%d \n",minnum[i]);
        }
    }
}
