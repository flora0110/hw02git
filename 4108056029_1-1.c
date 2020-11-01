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
    printf("in addq\n");
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

typedef struct Nodenum{
    int num;
    node* fromnode;
    int no;
}Nodenum;


typedef struct queue2* queuepointer2;
typedef struct queue2{
    Nodenum data;
    queuepointer2 link;
}queue2;

//typedef struct queue2* queuepointer2;
queuepointer2 front2[MAX_QUEUES],rear2[MAX_QUEUES];
Nodenum queueEmpty2(){
    printf("queue is empty\n");
    Nodenum item;
    item.num=-1;
    item.fromnode=NULL;
    item.no=-1;
    return item;
}
void addq2(Nodenum item,int i){
    queuepointer2 temp;
    temp=(queuepointer2)malloc(sizeof(queue2));
    temp->data=item;
    temp->link=NULL;
    if(front2[i]){
        rear2[i]->link=temp;
    }
    else
        front2[i]=temp;
    rear2[i]=temp;
}

Nodenum deleteq2(int i){
    queuepointer2 temp=front2[i];
    Nodenum item;
    if(!temp){
        return queueEmpty2();
    }
    item = temp->data;
    front2[i]=temp->link;
    free(temp);
    return item;
}

Nodenum minno(int i){
    int min=15001;
    Nodenum temp;
    queuepointer2 now=front2[i];
    while(now){
        if(now->data.num<min){
            min=now->data.num;
            temp=now->data;
            now=now->link;
        }
    }
    return temp;
}
node* maxno(int i){
    int max=-1;
    node* temp;
    queuepointer2 now=front2[i];
    while(now){
        if(now->data.num>max){
            temp=now->data.fromnode;
            now=now->link;
        }
    }
    return temp;

}
void postorder(node* ptr){
    if(ptr){
        printf("%d\n",ptr->data);
        postorder(ptr->left);
        postorder(ptr->right);

    }
}
int main(){
    int i,j;
    char c;
    //node* Root;
    node* root;
    c=getc(stdin);
    int n=0;
    //printf("[: %c\n",c);
    if(c=='['){//開始建立樹
        //printf("[: %c\n",c);
        c=getc(stdin);//抓根
        if(c=='0'){
            printf("root: %c\n",c);
            c=getc(stdin);
            //struct TreeNode root;
            printf("??\n");
            root->data=1;
            printf("ready to addq\n");
            addq(root);
            printf("out addq\n");
            n++;
        }
        while(front){
            printf("in while\n" );
            struct TreeNode* current;//現在在幫誰加葉子
            current=deleteq();
            if(c==']'){//結束
                break;
            }
            c=getc(stdin);
            if(c=='0'){
                printf("left: %c\n",c);
                //struct TreeNode newnode;//左葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                //current.left=&newnode;
                current->left=newnode;

                newnode->data=1;
                current->data=2;
                //printf("root's data %d\n",current.data);
                addq(newnode);
                n++;
            }
            else if(c=='n'){
                current->left=NULL;
                scanf("%*[ull]");//吃掉ull
            }
            getc(stdin);//吃','
            c=getc(stdin);
            if(c=='0'){
                printf("right: %c\n",c);
                //struct TreeNode newnode;//右葉
                node* newnode;
                newnode=(node*)malloc(sizeof(node));
                current->right=newnode;

                newnode->data=1;
                addq(newnode);
                n++;
            }
            else{
                current->right=NULL;
                scanf("%*[ull]");
            }
            c=getc(stdin);//eat ','or']'
        }//-----------------------------------------------完成樹
        printf("root's data %d\n",root->data);
        postorder(root);
        printf("bulid tree finish\n");
    }
    else{//輸入非以[開頭
        printf("input error\n");
    }
    printf("start to find\n");
    int lleaf,rleaf;
    //Nodenum nodenum[n][n];
    int den=0;//現在在檢查的有幾個子
    int leafden=0;//現在在檢查的的葉子有幾個子
    front=NULL;
    addq(root);
    int nownum=-1;//在檢查誰
    int leafnum=0;//丟值給子節點到幾號了
    //------------------------------------
    while(front!=rear){
        struct TreeNode* nowcheck=deleteq();
        nownum++;
        if(nowcheck->left){
            addq(nowcheck->left);//加到之後要檢查的
            den++;
        }
        if(nowcheck->right){
            addq(nowcheck->right);
            den++;
        }
        Nodenum nodenum;
        nodenum.num=nowcheck->data/(den+1);;
        nodenum.fromnode=nowcheck;
        nodenum.no=0;
        //nodenum.no=nownum;
        addq2(nodenum,nownum);//把自己的值/子+1 來自自己 addq2 queue2[nownum] 這個是給現在檢查的位置
        //nodenum[nownum][nowno].num=nowcheck.data/(den+1);//自己的值/den+1
        //nodenum[nownum][nowno].fromnode=&nowcheck;
        if(nowcheck->left){
            leafnum++;//在給幾號葉子值
            Nodenum leftnum;//父要給左子
            leftnum.num=nowcheck->data/(den+1);//父節點給子的值
            leftnum.fromnode=nowcheck;//來自父nownum
            leftnum.no=0;
            //leftnum.no=nodenum.no+1;//給左子下一個編號
            addq2(leftnum,leafnum);
            //nodenum[1][0].num=nowcheck.data/(den+1);
            //開始檢查左子有幾個子
            leafden=0;
            if(nowcheck->left->left){
                leafden++;
            }
            if(nowcheck->left->right){
                leafden++;
            }
            //左子要給父
            leftnum.no=0;
            leftnum.num=nowcheck->left->data/(leafden+2);
            leftnum.fromnode=nowcheck->left;//來自佐子
            addq2(leftnum,nownum);
        }
        if(nowcheck->right){
            leafnum++;//在給幾號葉子值
            Nodenum rightnum;//父要給右子
            rightnum.num=nowcheck->data/(den+1);//父節點給子的值
            rightnum.fromnode=nowcheck;//來自父nownum
            rightnum.no=0;
            addq2(rightnum,leafnum);

            //開始檢查左子有幾個子
            leafden=0;
            if(nowcheck->right->left){
                leafden++;//分母
            }
            if(nowcheck->right->right){
                leafden++;
            }
            //右子要給父
            rightnum.no=0;
            rightnum.num=nowcheck->right->data/(leafden+2);
            rightnum.fromnode=nowcheck->right;//來自右子
            addq2(rightnum,nownum);
        }
    }
    printf("finish find\n");
    printf("start to mark\n");
    int min=15001;
    for(i=0;i<nownum;i++){
        Nodenum minnodenum=minno(i);
        minnodenum.no++;
    }
    int mark[nownum];
    int ans=0;
    for(i=0;i<nownum;i++){
        node marknode=*maxno(i);
        if(marknode.data!=-1){
            ans++;
            marknode.data=-1;
        }
    }
}
