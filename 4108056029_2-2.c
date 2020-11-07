//優化方向 : 加上兩個一起做
//優化方向(時間) : 超過MIN時就break
#include <stdio.h>
#include <stdlib.h>
typedef struct howto{
    int toplat;//如何到那格月台(><)
    int tostat;////如何到那站(+-)
}howto;

int min;
howto fewstep(int now,int target,int* plat){//回傳到每個站的最快方法(howto)
    min=-1;//初始化min
    int i;
    howto ans;//要回傳的答案
    int sum;//目前走法的總步數
    int toplat,tostat;//目前的走法
    int right,left;//往右轉和左轉不同
    int pr,pl;//月台左右轉
    for(i=0;i<20;i++){
        if(i-now<0){
            pr=i+1+19-now;
        }
        else{
            pr=i-now;
        }
        if(now-i<0){
            pl=i+1+19-now;//向左轉到0再轉一到19,再轉19-now到now
        }
        else{
            pl=now-i;
        }
        toplat= (pr<pl)? pr:-pl;//左轉是負的
        if(target-plat[i]<0){
            right = (90-plat[i])+1+target-64;
        }
        else{
            right=target-plat[i];
        }
        if(plat[i]-target<0){//向左轉到64再轉1到90,再轉90-target到
            left = plat[i]-64+1+90-target;
        }
        else{
            left=plat[i]-target;
        }
        tostat= (right<left)? right:-left;
        sum=abs(tostat)+abs(toplat);
        if(min==-1 || sum<min){//min還在初始狀態或找到小的
            min=sum;
            ans.toplat=toplat;
            ans.tostat=tostat;
        }
    }
    return ans;
}
int main(){
    int i;
    int *plat=malloc(20*sizeof(int));
    for(i=0;i<20;i++){
        plat[i]=64;
    }
    FILE* rptr;
    FILE* wfile;
    rptr=fopen("test2-2.txt","r");
    wfile=fopen("output2-2.txt","w");
    if(rptr==NULL || wfile==NULL){
        printf("open failure\n");
        return 1;
    }
    else{
        min = -1;
        int now=0;
        char target;
        howto ans;
        int i;
        target=fgetc(rptr);
        int totalstep=0;
        while(target!='\n' && target!=EOF){
            ans=fewstep(now,target,plat);
            now+=ans.toplat;
            plat[now]=target;
            for(i=0;i<abs(ans.toplat);i++){
                if(ans.toplat>0){
                    fprintf(wfile,">");
                    printf(">");
                }
                else{
                    fprintf(wfile,"<");
                    printf("<");
                }
                totalstep++;
            }
            for(i=0;i<abs(ans.tostat);i++){
                if(ans.tostat>0){
                    fprintf(wfile,"+");
                    printf("+");
                }
                else{
                    fprintf(wfile,"-");
                    printf("-");
                }
                totalstep++;
            }
            fprintf(wfile,".");
            printf(".");
            totalstep++;
            target=fgetc(rptr);
        }
        printf("\ntotalstep :%d\n",totalstep );
    }
    fclose(rptr);
    fclose(wfile);
}
