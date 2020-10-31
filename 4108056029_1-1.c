#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode {
     int data;
     struct TreeNode* left;
     struct TreeNode* right;
};
typedef struct TreeNode node;
typedef struct queue* queuepointer;
typedef struct queue{
    node data;
    queuepointer link;
}queue;
queuepointer front=NULL,rear;

node queueEmpty(){
    printf("queue is empty\n");
    node item;
    item.data=-1;
    item.left=NULL;
    item.right=NULL;
    return item;
}
void addq(node item){
    queuepointer temp;
    temp=(queuepointer)malloc(sizeof(queue));
    temp->data=item;
    temp->link=NULL;
    if(front){
        rear->link=temp;
    }
    else
        front=temp;
    rear=temp;
}

node deleteq(){
    queuepointer temp=front;
    node item;
    if(!temp){
        return queueEmpty();
    }
    item = temp->data;
    front=temp->link;
    free(temp);
    return item;
}


int main(){
    int i,j;
    char c;
    c=getc(stdin);
    //printf("[: %c\n",c);
    if(c=='['){//開始建立樹
        //printf("[: %c\n",c);
        c=getc(stdin);//抓根
        if(c=='0'){
            //printf("0: %c\n",c);
            c=getc(stdin);
            struct TreeNode root;
            addq(root);
        }
        while(front!=rear){
            struct TreeNode current;//現在在幫誰加葉子
            current=deleteq();
            if(c==']'){//結束
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                //struct TreeNode newnode;//左葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                //current.left=&newnode;
                current.left=newnode;
                addq(*newnode);
            }
            else if(c=='n'){
                current.left=NULL;
                scanf("%*[ull]");//吃掉ull
            }
            getc(stdin);//吃','
            c=getc(stdin);
            if(c=='0'){
                struct TreeNode newnode;//右葉
                current.right=&newnode;
                addq(newnode);
            }
            else{
                current.right=NULL;
                scanf("%*[ull]");
            }
            c=getc(stdin);//eat ','or']'
        }//-----------------------------------------------完成樹
        printf("bulid tree finish\n");
    }
    else{//輸入非以[開頭
        printf("input error\n");
    }

    printf("start to find\n");
}
