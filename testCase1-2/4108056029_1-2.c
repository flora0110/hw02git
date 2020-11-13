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
int marknum=0;
/*int find(node* ptr){
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
    if(ptr->left){
        if(leftmark==-1){//左邊是x
            ptr->data=-2;//標#
            marknum++;
        }
        else if(leftmark==-2){//左邊是#
            ptr->data=-3;//標?
            ptr->left=NULL;
        }
    }
    if(ptr->right){
        if(rightmark==-1){//右邊是x
            if(leftmark!=-1){//#飆過
                ptr->data=-2;//標#
                marknum++;
            }
        }
        else if(rightmark==-2){//右邊是#
            if(leftmark!=-1){//#優先
                ptr->data=-3;//標?
            }
            ptr->right=NULL;
        }
    }
    if(ptr->data==-3 && (!ptr->left &&!ptr->right)){//沒有孩子的?要刪掉(視同null)
        ptr->data=-5;
    }
    return ptr->data;
}*/
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
    rptr=fopen("test2.txt","r");
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
        printf("bulid tree finish\n");
        postorder(root);
        /*if(root!=NULL){
            //find(root);
            if(root->data>=0 || root->data==-1){
                marknum++;
            }
        }
        printf("output: %d\n",marknum);*/
    }
}
