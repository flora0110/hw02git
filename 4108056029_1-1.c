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
}queue;
queuepointer front=NULL,rear;
element queueEmpty(){
    printf("queue is empty\n");
    element item;
    item.node.data=-1;
    item.node.left=NULL;
    item.node.right=NULL;
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
    char c;
    c=getc(stdin);
    if(c=='['){
        c=getc(stdin);
        if(c=='0'){
            c=getc(stdin);
            struct TreeNode root;
            element Root;
            Root.node=root;
            addq(Root);
        }
        while(front!=rear){
            struct TreeNode current;
            element Current;
            Current.node=current;
            Current=deleteq();
            if(c==']'){
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                struct TreeNode newnode;
                element Newnode;
                Newnode.node=newnode;
                Current.node.left=&newnode;
                addq(Newnode);
            }
            else{
                Current.node.left=NULL;
                scanf("%*[ull]");
            }
            getc(stdin);//吃','
            c=getc(stdin);
            if(c=='0'){
                struct TreeNode newnode;
                element Newnode;
                Newnode.node=newnode;
                Current.node.right=&newnode;
                addq(Newnode);
            }
            else{
                Current.node.right=NULL;
                scanf("%*[ull]");
            }
            c=getc();//eat ','or']'
        }//-----------------------------------------------完成樹
        printf("tree finish\n");
    }

    else{//輸入非以[開頭
        printf("input error\n");
    }
}
