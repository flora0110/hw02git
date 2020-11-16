#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
        printf("%d\n",ptr->data);
        postorder(ptr->left);
        postorder(ptr->right);
    }
}
int marknum=0;
int find(node* ptr){

    if(ptr==NULL){//到NULL -5
        return -5;
    }
    int leftmark=find(ptr->left);
    int rightmark=find(ptr->right);
    if(leftmark==-5 && ptr->left){
        ptr->left=NULL;
    }
    if(rightmark==-5 && ptr->right){
        ptr->right=NULL;
    }
    if(leftmark==-5 && rightmark==-5){
        ptr->data=-1;
    }
    //檢查左邊
    else if(ptr->left){
        if(leftmark==-1){//左邊是x
            ptr->data=-2;//標#
            marknum++;
        }
        else if(leftmark==-2){//左邊是#
            ptr->data=-3;//標?
            ptr->left=NULL;
        }
    }
    else if(ptr->right){
        if(rightmark==-1){//右邊是x
            ptr->data=-2;//標#
            marknum++;
        }
        else if(rightmark==-2){//右邊是#
            ptr->data=-3;//標?
            ptr->right=NULL;
        }
    }
    if(ptr->data==-3 || (!ptr->left &&!ptr->right)){//沒有孩子的?要刪掉(視同null)
        ptr->data=-5;
    }
    return ptr->data;
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("");
    int i,j;
    char c;
    //node* Root;
    node* root;
    root=(node*)malloc(sizeof(node));
    c=getc(stdin);
    int n=0;
    //printf("[: %c\n",c);
    //int test=1;
    if(c=='['){//開始建立樹
        //printf("[: %c\n",c);
        c=getc(stdin);//抓根
        if(c=='0'){
            //printf("root: %c\n",c);
            c=getc(stdin);
            //struct TreeNode root;
            //printf("??\n");
            root->data=0;
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
            c=getc(stdin);
            if(c=='0'){
                //printf("left: %c\n",c);
                //struct TreeNode newnode;//左葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                //current.left=&newnode;
                current->left=newnode;
                newnode->data=0;
                newnode->left=NULL;
                newnode->right=NULL;
                //printf("root's data %d\n",current.data);
                addq(newnode);
                //printf("out addq\n");
                n++;
            }
            else if(c=='n'){
                current->left=NULL;
                scanf("%*[ull]");//吃掉ull
            }
            c=getc(stdin);//吃','
            if(c==']'){
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                //printf("right: %c\n",c);
                //struct TreeNode newnode;//右葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                current->right=newnode;
                newnode->left=NULL;
                newnode->right=NULL;
                newnode->data=0;
                addq(newnode);
                n++;
            }
            else{
                current->right=NULL;
                scanf("%*[ull]");
            }
            c=getc(stdin);//eat ','or']'
            //printf("root's data %d\n",root->data);
        }//-----------------------------------------------完成樹
        printf("root's data %d\n",root->data);
        postorder(root);
        printf("bulid tree finish\n");
    }
    else{//輸入非以[開頭
        printf("input error\n");
    }
    printf("start to find\n");
    find(root);
    printf("output: %d\n",marknum);
}
