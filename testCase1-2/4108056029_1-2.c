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
typedef struct stack* stackpointer;
typedef struct stack{
    node* nodeptr;
    stackpointer link;
    stackpointer qulink;
}stack;
stackpointer top=NULL,front3=NULL,rear3;
int nodeptrn=0;
void push(node* item){
    stackpointer temp=(stackpointer)malloc(sizeof(stack));
    temp->nodeptr=item;
    temp->link=top;
    temp->qulink=NULL;
    if(front3){
        rear3->qulink=temp;
    }
    else
        front3=temp;
    rear3=temp;
    top=temp;
    nodeptrn++;
    if(nodeptrn>5){
        stackpointer temp2=front3;
        if(!temp2){
            printf("error\n");
        }
        front3=temp2->qulink;
        free(temp2);
        nodeptrn--;
    }
}
node* pop(){
    stackpointer temp=top;
    node* item;
    if(top){
        item=top->nodeptr;
        top=temp->link;
        free(temp);
        return item;
    }
}

typedef struct imfor{
    int data;//節點裡的值
    int mark;//標記
    int temp[3];//c1 c2 f
}imfor;
int min;
int numarray[15000];
int minnum[15000];
int sum=0;
int count=0;
int mincount;
int checkn=0;//需要check 的點
stackpointer top;
imfor find (node* ,node* ,char ,int );
int nearby(char c,int sum){
    node* a=pop();
    if(c=='l'){
        imfor ar=find(a->right,a,'r',1);
        if(ar.mark==-2 || ar.mark==-4){
            push(a);
            return 1;
        }
        if(ar.mark==-3){
            if(ar.temp[1]==-1){
                ar.temp[1]=0;
            }
            if((ar.data-(ar.temp[0]+ar.temp[1])) < sum ){
                push(a);
                return 1;
            }
            else {
                ar.mark=-1;
            }

        }
        if(ar.mark==-1){
            node *f=pop();
            if(f==NULL){
                return 0;
            }
            else{
                f->data-=sum;
                push(f);
                push(a);
                return 3;
            }
        }

    }
}
imfor find (node* ptr,node* fatherptr,char c,int switch2){
    push(ptr);
    int i;
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
    int fatherdata=fatherptr->data;
    imfor leftimfor=find(ptr->left,ptr,'l',switch2);
    imfor rightimfor=find(ptr->right,ptr,firsttime,'r',switch2);
    int rightdata=rightimfor.data;
    int rightmark=rightimfor.mark;
    int leftdata=leftimfor.data;
    int leftmark=leftimfor.mark;
    int temp1[3];
    int temp2[3];
    int leaf1[3];
    int leaf2[3];
    int isf1=0,isf2=0;
    int leaff1=0,leaff2=0;
    if(leftmark==-9){
        for(i=0;i<3;i++){
            nowimfor.temp[i]=leftimfor.temp[i];
        }
        nowimfor.mark=-10;
        return nowimfor;
    }
    if(rightmark==-9){
        for(i=0;i<3;i++){
            nowimfor.temp[i]=rightimfor.temp[i];
        }
        nowimfor.mark=-10;
        return nowimfor;
    }
    if(leftmark==-10&&rightmark==-1 || rightmark==-10&&leftmark==-1){
        for(i=0;i<3;i++){
            nowimfor.temp[i]=leftimfor.temp[i];
        }
        nowimfor.mark=-20;
        return nowimfor;
    }
    if(leftmark==-20){
        for(i=0;i<3;i++){
            leaf1[i]=leftimfor.temp[i];
        }
        leftmark=-2;
        leaff1=1;
    }
    if(rightmark==-20){
        for(i=0;i<3;i++){
            leaf2[i]=rightimfor.temp[i];
        }
        rightmark=-2;
        leaff2=1;
    }
    if(leftmark==-10){
        for(i=0;i<3;i++){
            temp1[i]=leftimfor.temp[i];
        }
        leftmark=-1;
        isf1=1;
    }
    if(rightmark==-10){
        for(i=0;i<3;i++){
            temp2[i]=rightimfor.temp[i];
        }
        rightmark=-1;
        isf2=1;
    }
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
        if(leftmark==-1){
            nowimfor.mark=-1;
        }
    }
    //printf("\nnowmark %d\n",nowimfor.mark );
    //printf("leftmark: %d    rightmark: %d\n",leftmark,rightmark );
    if(leftmark==-1 && rightmark==-1 && nowimfor.mark!=-1){
        //printf("-------------------%d is x\n",ptr->data);
        nowimfor.mark=-2;
    }
    else if(leftmark==-2 || rightmark==-2){
        //nowimfor.mark=-3;
        int case=0;
        if(ptr->data>(rightdata+leftdata) && ptr->data<(rightdata+leftdata+fatherdata)){
            nowimfor.mark=-3;
            if(swich2){
                int p;
                if(leftmark==-2){
                    nowimfor.temp[p++]=leftdata;
                }
                if(rightmark==-2){
                    nowimfor.temp[p++]=rightdata;
                }
                nowimfor.temp[2]=ptr->data;
                return nowimfor;
            }
            int check = nearby(c,ptr->data-leftdata-rightdata);
            if(check==1){
                case=-5;
            }
            else if(case==0){
                case=-4;
            }
            else if(check==3){
                nowimfor.mark=-9;
            }
        }
        if(ptr->data<(rightdata+leftdata) ||(case==-4)){
            //printf("------------------------%d is case -4\n",ptr->data);
            //先恢復ptr->data
            if(isf1){
                if(temp1[1]==-1){
                    ptr->data+=temp1[2]-temp1[0];
                }
                else{
                    ptr->data+=temp1[2]-temp1[1]-temp1[0];
                }
            }
            if(isf2){
                if(temp2[1]==-1){
                    ptr->data+=temp2[2]-temp2[0];
                }
                else{
                    ptr->data+=temp2[2]-temp2[1]-temp2[0];
                }
            }
            //----------------------
            if(isf1){
                if(temp1[1]!=-1){
                    numarray[count++]=temp1[1];
                    sum+=temp1[0]+temp1[1];
                }
                else{
                    sum+=temp1[0];
                }
                numarray[count++]=temp1[0];
            }
            if(isf2){
                if(temp2[1]!=-1){
                    numarray[count++]=temp2[1];
                    sum+=temp2[0]+temp2[1];
                }
                else{
                    sum+=temp2[0];
                }
                numarray[count++]=temp2[0];
            }
            nowimfor.mark=-4;
            numarray[count++]=ptr->data;
            sum+=ptr->data;
            if(leaff1){
                numarray[count++]=leaf1[2];
            }
            if(leaff2){
                numarray[count++]=leaf2[2];
            }
            //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
        }
        else if((ptr->data>(rightdata+leftdata+fatherdata))||case==-5){
            if(leaff1){
                if(leaf1[1]==-1){
                    leftdata+=leaf1[2]-leaf1[0];
                    ptr->left->data=leftdata;
                }
                else{
                    leftdata+=leaf1[2]-leaf1[1]-leaf1[0];
                    ptr->left->data=leftdata;
                }
            }
            if(leaff2){
                if(leaf2[1]==-1){
                    leftdata+=leaf2[2]-leaf2[0];
                    ptr->left->data=leftdata;
                }
                else{
                    leftdata+=leaf2[2]-leaf2[1]-leaf2[0];
                    ptr->left->data=leftdata;
                }
            }
            //printf("------------------------%d is case -5\n",ptr->data);
            if(leftmark==-2){

                if(leaff1){
                    if(leaf1[1]!=-1){
                        numarray[count++]=leaf1[1];
                        sum+=leaf1[0]+leaf1[1];
                    }
                    else{
                        sum+=leaf1[0];
                    }
                    numarray[count++]=leaf1[0];
                }
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
                if(leaff2){
                    if(leaf2[1]!=-1){
                        numarray[count++]=leaf2[1];
                        sum+=leaf2[0]+leaf2[1];
                    }
                    else{
                        sum+=leaf2[0];
                    }
                    numarray[count++]=leaf2[0];
                }
                //printf("right %d\n",rightdata);
                //printf("numarray[%d] %d\n",count-1, numarray[count-1]);
            }
            if(isf1){
                numarray[count++]=temp1[0];
                numarray[count++]=temp1[1];
            }
            if(isf1){
                numarray[count++]=temp2[0];
                numarray[count++]=temp2[1];
            }
            //printf("sum: %d\n",sum );
            nowimfor.mark=-1;
        }

    }
    //printf("finish------------ptr->data %d %d\n",ptr->data,nowimfor.mark);
    return nowimfor;
}
//--------------------------可能性
int testn=0;
node *root;
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
            imfor rootim =find(root,NULL,'l',0);//第一次
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
            printf("$%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%testn %d checkn %d\n",testn,checkn );

        }
        printf("output: %d\n",min);
        for(i=0;i<mincount;i++){
            printf("%d \n",minnum[i]);
        }
    }
}
