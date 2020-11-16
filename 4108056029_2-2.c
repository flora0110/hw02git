//優化方向 : 加上兩個一起做
//優化方向(時間) : 超過MIN時就break
//防止爆三秒 #include<time.h>
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
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

typedef struct howto2{
    int toplat;//如何到那格月台(><)
    int tostat;////如何到那站(+-)
    int toplat2;//如何到那格月台(><)
    int tostat2;////如何到那站(+-)

}howto2;
howto2 fewstep2(int now,int target,int target2,int* plat){//回傳到每個站的最快方法(howto)
    min=-1;//初始化min
    int i,j;
    howto2 ans;//要回傳的答案
    int sum;//目前走法的總步數
    int toplat,tostat;//目前的走法
    int right,left;//往右轉和左轉不同
    int pr,pl;//月台左右轉
    int sum2;//目前走法的總步數
    int toplat2,tostat2;//目前的走法
    int right2,left2;//往右轉和左轉不同
    int pr2,pl2;//月台左右轉
    int temp;
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
        //printf("toplat %d\n",toplat );
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
        //printf("tostat %d\n",tostat);
        sum=abs(tostat)+abs(toplat);
        //printf("sum %d\n",sum );
        temp=plat[i];
        plat[i]=target;
        /*if(target2=='M'){
            printf("---------------i %d %c\n",i ,target2);
        }*/

        for(j=0;j<20;j++){//i->j now->i

            /*if(target2=='M'){
                printf("j %d %c\n",j,plat[j] );
            }*/
            if(j-i<0){
                pr2=j+1+19-i;
            }
            else{
                pr2=j-i;
            }
            /*if(target2=='M'){
                printf("pr2 %d\n",pr2 );
            }*/
            if(i-j<0){
                pl2=j+1+19-i;//向左轉到0再轉一到19,再轉19-now到now
            }
            else{
                pl2=i-j;
            }
            /*if(target2=='M'){
                printf("pl2 %d\n",pl2 );
            }*/
            toplat2= (pr2<pl2)? pr2:-pl2;//左轉是負的
            //printf("toplat2 %d\n",toplat2 );
            if(target2-plat[j]<0){
                right2 = (90-plat[j])+1+target2-64;
            }
            else{
                right2=target2-plat[j];
            }/*
            if(target2=='M'){
                printf("right2 %d\n",right2 );
            }
            if(target2=='M'){
                printf("j %d %c\n",j,plat[j] );
            }*/
            if(plat[j]-target2<0){//向左轉到64再轉1到90,再轉90-target到
                left2 = plat[j]-64+1+90-target2;
            }
            else{

                left2=plat[j]-target2;
            }
            /*
            if(target2=='M'){
                printf("left2 %d\n",left2 );
            }*/

            tostat2= (right2<left2)? right2:-left2;
            //printf("tostat2 %d\n",tostat2);
            sum2=abs(tostat2)+abs(toplat2);
            //printf("sum2 %d\n",sum2 );
            //printf("sum+sum2 = %d\n\n",sum+sum2 );
            if(min==-1 || sum+sum2<min){//min還在初始狀態或找到小的
                min=sum+sum2;
                ans.toplat=toplat;
                ans.tostat=tostat;
                ans.toplat2=toplat2;
                ans.tostat2=tostat2;
            }

        }
        plat[i]=temp;
    }
    return ans;
}
int main(){
    int i;
    int *plat=malloc(20*sizeof(int));
    int *plat2=malloc(20*sizeof(int));
    for(i=0;i<20;i++){
        plat[i]=64;
        plat2[i]=plat[i];
    }
    FILE* rptr;
    FILE* wfile;
    rptr=fopen("test2-2.txt","r");//testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest
    wfile=fopen("output2-2.txt","w");
    if(rptr==NULL || wfile==NULL){
        printf("open failure\n");
        return 1;
    }
    else{
        min = -1;
        int now=0;
        int now2=0;
        char target;
        char lasttarget;
        howto ans;
        howto2 ans2;
        int i;
        int count=1;
        char *command;
        char *command2;
        MALLOC(command,10000*sizeof(char));
        MALLOC(command2,10000*sizeof(char));
        target=fgetc(rptr);
        int totalstep=0;
        int totalstep2=0;
        int j1=0,j2=0;
        while(target!='\n' && target!=EOF){
            if(target==' '){
                target='@';
                //printf("\n\n" );
            }
            ans=fewstep(now,target,plat);
            now+=ans.toplat;
            plat[now]=target;
            for(i=0;i<abs(ans.toplat);i++){
                if(ans.toplat>0){
                    //printf(">");
                    command[j1++]='>';
                }
                else{
                    //printf("<");
                    command[j1++]='<';
                }
                totalstep++;
            }
            for(i=0;i<abs(ans.tostat);i++){
                if(ans.tostat>0){
                    //printf("+");
                    command[j1++]='+';
                }
                else{
                    //printf("-");
                    command[j1++]='-';
                }
                totalstep++;
            }
            //printf(".");
            command[j1++]='.';
            totalstep++;
            //printf("totalstep %d\n",totalstep);
            if(count==1){
                lasttarget=target;
                count++;
            }
            else if(count==2){
                count=1;
                ans2=fewstep2(now2,lasttarget,target,plat2);
                now2+=ans2.toplat;
                plat2[now2]=lasttarget;
                for(i=0;i<abs(ans2.toplat);i++){
                    if(ans2.toplat>0){
                        //printf(">");
                        command2[j2++]='>';
                    }
                    else{
                        //printf("<");
                        command2[j2++]='<';
                    }
                    totalstep2++;
                }
                for(i=0;i<abs(ans2.tostat);i++){
                    if(ans2.tostat>0){
                        //printf("+");
                        command2[j2++]='+';
                    }
                    else{
                        //printf("-");
                        command2[j2++]='-';
                    }
                    totalstep2++;
                }
                //printf(".");
                //printf(" %d %c\n",now2,lasttarget );
                command2[j2++]='.';
                totalstep2++;
                now2+=ans2.toplat2;
                plat2[now2]=target;
                for(i=0;i<abs(ans2.toplat2);i++){
                    if(ans2.toplat2>0){
                        //printf(">");
                        command2[j2++]='>';
                    }
                    else{
                        //printf("<");
                        command2[j2++]='<';
                    }
                    totalstep2++;
                }
                for(i=0;i<abs(ans2.tostat2);i++){
                    if(ans2.tostat2>0){
                        //printf("+");
                        command2[j2++]='+';
                    }
                    else{
                        //printf("-");
                        command2[j2++]='-';
                    }
                    totalstep2++;
                }
                //printf(".");
                command2[j2++]='.';
                totalstep2++;
                //printf(" %d %c\n",now2,target );
                //printf("\n--- totalstep2 %d---\n",totalstep2 );
            }

            target=fgetc(rptr);
        }
        if(count==2){
            //printf("odd\n");
            ans=fewstep(now2,target,plat2);
            now2+=ans.toplat;
            plat2[now2]=target;
            for(i=0;i<abs(ans.toplat);i++){
                if(ans.toplat>0){
                    //printf(">");
                    command2[j2++]='>';
                }
                else{
                    //printf("<");
                    command2[j2++]='<';
                }
                totalstep2++;
            }
            for(i=0;i<abs(ans.tostat);i++){
                if(ans.tostat>0){
                    //printf("+");
                    command2[j2++]='+';
                }
                else{
                    //printf("-");
                    command2[j2++]='-';
                }
                totalstep2++;
            }
            //printf(".");
            command2[j2++]='.';
            totalstep2++;
        }
        printf("\ntotalstep1 %d \n",totalstep );
        if(totalstep<=totalstep2){
            for(i=0;i<j1;i++){
                printf("%c",command[i]);
                fprintf(wfile,"%c",command[i]);
            }
            //printf("\ntotalstep :%d\n",totalstep );
            fprintf(wfile,"\ntotalstep :%d\n",totalstep );
        }
        else{
            for(i=0;i<j2;i++){
                printf("%c",command2[i]);
                fprintf(wfile,"%c",command2[i]);
            }
            //printf("\ntotalstep :%d\n",totalstep2 );
            fprintf(wfile,"\ntotalstep :%d\n",totalstep );
        }
    }
    fclose(rptr);
    fclose(wfile);
}
