#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
//--------------------------可能性
typedef struct List* listpointer;
typedef struct List{
    int* data;
    listpointer link;
}list;
listpointer front3,rear3;
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
}
int checkn=0;
void dfs(int *temp,int i){
    int j;
    if(i==checkn){
        int *item=(int*)malloc(checkn*sizeof(int));//小心指標會一起改
        for(j=0;j<checkn;j++){
            item[j]=temp[j];
        }
        addq3(item);
        return;
    }
    temp[i]=1;
    dfs(temp,i+1);
    temp[i]=2;
    dfs(temp,i+1);
}

typedef struct imfor{
    int data;//節點裡的值
    int mark;//標記
}imfor;
int min;
int numarray[15000];
int minnum[15000];
int sum;
int count=0;
int mincount;
queuepointer2 top;
imfor find (node* ptr,int fatherdata,int firsttime){
    imfor nowimfor;
    if(ptr==NULL){
        nowimfor.data=0;
        nowimfor.mark=-1;
        return nowimfor;
    }
    nowimfor.data=ptr->data;
    imfor rightimfor=find(ptr->right,ptr->data,firsttime);
    imfor leftimfor=find(ptr->left,ptr->data,firsttime);
    int rightdata=rightimfor.data;
    int rightmark=rightimfor.mark;
    int leftdata=leftimfor.data;
    int leftmark=leftimfor.mark;
    if(leftmark==-5){
        ptr->left==NULL;
        leftmark=-1;
        leftdata=0;
    }
    if(rightmark==-5){
        ptr->right==NULL;
        rightmark=-1;
        rightdata=0;
    }
    if(leftmark==-4 &&(rightmark!=-2)){
        ptr->left==NULL;
        rightmark=-1;
        rightdata=0;
    }
    if(rightmark==-4&&(leftmark!=-2)){
        ptr->right==NULL;
        rightmark=-1;
        rightdata=0;
    }
    if(leftmark==-1 && rightmark==-1){
        nowimfor.mark=-2;
    }
    else if(leftmark==-2 || rightmark==-2){
        if(ptr->data<(rightdata+leftdata)){
            nowimfor.mark=-4;
            numarray[count++]=ptr->data;
            sum+=ptr->data;
        }
        else if(ptr->data>(rightdata+leftdata+fatherdata)){
            if(rightmark!=-1){
                sum+=rightdata;
                numarray[count++]=rightdata;
            }
            if(leftmark!=-1){
                sum+=leftdata;
                numarray[count++]=leftdata;
            }
            nowimfor.mark=-5;
        }
        else{
            int way=1;
            if(firsttime){
                element e;
                e.nodepointer=ptr;
                e.way=1;
                addq2(e);
                count++;
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
                nowimfor.mark=-4;
                numarray[count++]=ptr->data;
                sum+=ptr->data;
            }
            else if(way==2){
                if(rightmark!=-1){
                    sum+=rightdata;
                    numarray[count++]=rightdata;
                }
                if(leftmark!=-1){
                    sum+=leftdata;
                    numarray[count++]=leftdata;
                }
                nowimfor.mark=-5;
            }
        }


    }

    return nowimfor;
}

int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test1.txt","r");
    if(rptr==NULL){
        printf("ERROR\n");
        return 0;
    }
    else{
        int i,j;
        char c;
        node* root;
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
                printf("%s\n",str);
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
                printf("%s\n",str);
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
            find(root,0,1);
            int *temp=(int*)malloc(count*sizeof(int));
            dfs(temp,0);//把可能性弄完
            min=sum;
            int *check;
            //int minnum[100];
            mincount=count;
            while(front3){
                count=0;
                check=deleteq3();
                queuepointer2 nptr=front2;
                for(i=0;i<checkn;i++){
                    nptr->e.way=check[i];
                    nptr=nptr->link;
                }
                top=front2;
                find(root,0,0);
                if(sum<min){
                    memcpy(minnum,numarray,sizeof(num));
                    /*for(i=0;i<count;i++){
                        minnum[i]=num[i];
                    }*/
                    min=sum;
                    mincount=count;
                }
            }
        }
        printf("output: %d\n",sum);
        for(i=0;i<mincount;i++){
            printf("%d \n",minnum[i]);
        }
    }
}
