#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode {
     int data;
     struct node* left;
     struct node* right;
};
typedef struct{
    struct TreeNode node;
}element;
typedef struct queue* queuepointer;
typedef struct queue{
    element data;
    queuepointer link;
}
queuepointer front=NULL,rear;
element queueEmpty(){
    printf("queue is empty\n");
    element item;
    item.data=-1;
    item.left=NULL;
    item.right=NULL;
    return item;
}
void addq(element item){
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
element deleteq(){
    queuepointer temp=front;
    element item;
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
    char c=getc();
    if(c=='['){
        c=getc();
        if(c=='0'){
            c=getc();
            struct TreeNode root;
            addq(root);
        }
        while(front!=rear){
            struct TreeNode current;
            current=deleteq();
            if(c==']'){
                break;
            }
            c=getc();
            if(c=='0'){
                struct TreeNode newnode;
                current.left=&newnode;
                addq(newnode);
            }
            else{
                current.left=NULL;
                scanf("%*[ull]");
            }
            getc();//吃','
            c=getc();
            if(c=='0'){
                struct TreeNode newnode;
                current.right=&newnode;
                addq(newnode);
            }
            else{
                current.right=NULL;
                scanf("%*[ull]");
            }
            c=getc();//eat ','or']'
        }
    }
    else{//輸入非以[開頭
        printf("input error\n");
    }
}
