#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_QUEUES 100
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

typedef struct Nodenum{
    int num;
    node* fromnode;
    int no;
}Nodenum;

typedef struct queue{
    Nodenum data;
    queuepointer link;
}queue2;
queuepointer front2[MAX_QUEUES],rear2[MAX_QUEUES];
Nodenum queueEmpty(){
    printf("queue is empty\n");
    Nodenum item;
    item.num=-1;
    item.fromnode=NULL;
    item.no=-1;
    return item;
}
void addq2(Nodenum item,int i){
    queuepointer temp;
    temp=(queuepointer)malloc(sizeof(queue));
    temp->data=item;
    temp->link=NULL;
    if(front[i]){
        rear2[i]->link=temp;
    }
    else
        front2[i]=temp;
    rear2[i]=temp;
}

Nodenum deleteq2(int i){
    queuepointer temp=front2[i];
    node item;
    if(!temp){
        return queueEmpty();
    }
    item = temp->data;
    front2[i]=temp->link;
    free(temp);
    return item;
}


int main(){
    int i,j;
    char c;
    node* Root;
    c=getc(stdin);
    int n=0;
    //printf("[: %c\n",c);
    if(c=='['){//開始建立樹
        //printf("[: %c\n",c);
        c=getc(stdin);//抓根
        if(c=='0'){
            //printf("0: %c\n",c);
            c=getc(stdin);
            struct TreeNode root;
            root.data=1;
            addq(root);
            n++;
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
                newnode.data=1;
                addq(*newnode);
                n++;
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
                newnode.data=1;
                addq(newnode);
                n++;
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
    int lleaf,rleaf,i;
    //Nodenum nodenum[n][n];
    for(i=0;i<n;i++){
        nodenum[i][0].no=0;
    }
    int den=0;//現在在檢查的有幾個子
    int leafden=0;//現在在檢查的的葉子有幾個子
    front=NULL;
    addq(root);
    int nownum=-1;//在檢查誰
    int leafnum=0;//丟值給子節點到幾號了
    //------------------------------------
    TreeNode nowcheck=deleteq();
    nownum++;
    if(nowcheck.left){
        addq(*nowcheck.left);//加到之後要檢查的
        den++;
    }
    if(nowcheck.right){
        addq(*nowcheck.right);
        den++;
    }
    Nodenum nodenum;
    nodenum.num=nowcheck.data/(den+1);;
    nodenum.fromnode=&nowcheck;
    //nodenum.no=nownum;
    addq2(nodenum,nownum);//把自己的值/子+1 來自自己 addq2 queue2[nownum] 這個是給現在檢查的位置
    //nodenum[nownum][nowno].num=nowcheck.data/(den+1);//自己的值/den+1
    //nodenum[nownum][nowno].fromnode=&nowcheck;
    if(nowcheck.left){
        leafnum++;
        Nodenum leftnum;//父要給左子
        leftnum.num=nowcheck.data/(den+1);//父節點給子的值
        leftnum.fromnode=&nowcheck;//來自父nownum
        //leftnum.no=nodenum.no+1;//給左子下一個編號
        addq2(leftnum,leafnum);
        //nodenum[1][0].num=nowcheck.data/(den+1);
        //開始檢查左子有幾個子
        leafden=0;
        if(nowcheck.left->left){
            leafden++;
        }
        if(nowcheck.left->right){
            leafden++;
        }
        //左子要給父
        leftnum.num=nowcheck.left->data/(leafden+2);
        leftnum.fromnode=nowcheck.left;//來自佐子
        addq2(leftnum,nownum);
    }
    if(nowcheck.right){
        leafnum++;
        Nodenum rightnum;//父要給右子
        rightnum.num=nowcheck.data/(den+1);//父節點給子的值
        rightnum.fromnode=&nowcheck;//來自父nownum
        addq2(rightnum,leafnum);

        //開始檢查左子有幾個子
        leafden=0;
        if(nowcheck.right->left){
            leafden++;
        }
        if(nowcheck.right->right){
            leafden++;
        }
        //右子要給父
        leftnum.num=nowcheck.right->data/(leafden+2);
        leftnum.fromnode=nowcheck.right;//來自右子
        addq2(rightnum,nownum);
    }

}
