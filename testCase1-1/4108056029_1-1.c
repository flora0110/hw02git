#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_QUEUES 15000
struct TreeNode {
     int data;
     int n;
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
    //printf("in addq\n");
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

void postorder(node* ptr){
    if(ptr){
        printf("%d\n",ptr->n);
        postorder(ptr->left);
        postorder(ptr->right);
    }
}
int marknum=0;
int find(node* ptr){
    //printf("in find\n");
    if(ptr==NULL){//到NULL -5
        printf("null\n");
        //printf("%d arrive 空 \n",ptr->n);
        return -5;
    }
    //printf("in left\n");
    int leftmark=find(ptr->left);
    printf("%d's left is %d\n",ptr->n,leftmark );
    //printf("out left\n");
    //printf("in right\n");
    int rightmark=find(ptr->right);
    //printf("%d\n",rightmark );
    printf("%d's right is %d\n",ptr->n,rightmark );
    //printf("out right\n");
    if(leftmark==-5 && ptr->left){
        ptr->left=NULL;
    }
    if(rightmark==-5 && ptr->right){
        ptr->right=NULL;
    }
    if(leftmark==-5 && rightmark==-5){
        printf("-----------------------------------%d X\n",ptr->n);
        ptr->data=-1;
    }
    //檢查左邊
    if(ptr->left){
        printf("check left\n");
        if(leftmark==-1){//左邊是x
            printf("-----------------------------------%d #\n",ptr->n);
            ptr->data=-2;//標#
            marknum++;
        }
        else if(leftmark==-2){//左邊是#
            printf("-----------------------------------%d ?\n",ptr->n);
            ptr->data=-3;//標?
            ptr->left=NULL;
        }
    }
    if(ptr->right){
        printf("check right\n");
        if(rightmark==-1){//右邊是x
            //printf("-----------------------------------%d #\n",ptr->n);
            //ptr->data=-2;//標#
            //marknum++;
            if(leftmark!=-1){//#飆過
                printf("-----------------------------------%d #\n",ptr->n);
                ptr->data=-2;//標#
                marknum++;
            }
        }
        else if(rightmark==-2){//右邊是#
            if(leftmark!=-1){//#優先
                printf("-----------------------------------%d ?\n",ptr->n);
                ptr->data=-3;//標?
            }
            ptr->right=NULL;
        }
    }
    if(ptr->data==-3 && (!ptr->left &&!ptr->right)){//沒有孩子的?要刪掉(視同null)
        ptr->data=-5;
    }
    printf("ptr->data %d\n",ptr->data);
    return ptr->data;
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test7.txt","r");
    if(rptr==NULL){
        printf("ERROR\n");
        return 0;
    }
    else{
    printf("open!\n" );
    int i,j;
    char c;
    //node* Root;
    node* root;
    root=NULL;
    c=fgetc(rptr);
    int n=0;
    //printf("[: %c\n",c);
    int test=1;
    if(c=='['){//開始建立樹
        //printf("[: %c\n",c);
        c=fgetc(rptr);//抓根
        if(c=='0'){
            root=(node*)malloc(sizeof(node));
            //printf("root: %c\n",c);
            c=fgetc(rptr);
            //struct TreeNode root;
            //printf("??\n");
            root->data=0;
            root->n=test++;
            //printf("ready to addq\n");
            addq(root);
            //printf("out addq\n");
            n++;
        }
        while(front){
            //printf("in while\n" );
            struct TreeNode* current;//現在在幫誰加葉子
            current=deleteq();
            if(c==']'){//結束
                break;
            }
            c=fgetc(rptr);
            if(c=='0'){
                //printf("left: %c\n",c);
                //struct TreeNode newnode;//左葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                //current.left=&newnode;
                current->left=newnode;
                newnode->data=0;
                newnode->n=test++;
                newnode->left=NULL;
                newnode->right=NULL;
                //printf("root's data %d\n",current.data);
                addq(newnode);
                //printf("out addq\n");
                n++;
            }
            else if(c=='n'){
                current->left=NULL;
                fscanf(rptr,"%*[ull]");//吃掉ull
            }
            c=fgetc(rptr);//吃','
            if(c==']'){
                break;
            }
            c=fgetc(rptr);
            if(c=='0'){
                //printf("right: %c\n",c);
                //struct TreeNode newnode;//右葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                current->right=newnode;
                newnode->left=NULL;
                newnode->right=NULL;
                newnode->data=0;
                newnode->n=test++;
                addq(newnode);
                n++;
            }
            else{
                current->right=NULL;
                fscanf(rptr,"%*[ull]");
            }
            c=fgetc(rptr);//eat ','or']'
            //printf("root's data %d\n",root->data);
        }//-----------------------------------------------完成樹
        if(root!=NULL){
            printf("root's data %d\n",root->n);
            postorder(root);
        }

        printf("bulid tree finish\n");
    }
    else{//輸入非以[開頭
        printf("input error\n");
    }
    if(root!=NULL){
        printf("start to find\n");
        find(root);
        if(root->data>=0 || root->data==-1){
            marknum++;
        }
    }

    printf("output: %d\n",marknum);
}
}
