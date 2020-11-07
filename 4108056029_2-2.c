#include <stdio.h>
#include <stdlib.h>
typedef struct howto{
    int toplat;
    int tostat;
}howto;

int min;
howto fewstep(int now,int target,int* plat){
    //printf("now %d target %d\n",now ,target );
    min=-1;
    int i;
    howto ans;
    int sum;
    int toplat,tostat;
    int right,left;
    for(i=0;i<20;i++){
        toplat = i-now;
        //printf("toplat %d\n",toplat );
        if(target-plat[i]<0){
            //printf("plat[i] %d\n",plat[i] );
            right = (90-plat[i])+1+target-64;
            //printf("right %d\n",right);
        }
        else{
            right=target-plat[i];
            //printf("right %d\n",right);
        }
        if(plat[i]-target<0){
            left = plat[i]-64+1+90-target;
            //printf("left %d\n",left);
        }
        else{
            left=plat[i]-target;
            //printf("left %d\n",left);
        }
        tostat= (right<left)? right:-left;
        //printf("tostat %d\n",tostat);
        sum=abs(tostat)+abs(toplat);
        if(min==-1 || sum<min){
            min=sum;
            ans.toplat=toplat;
            ans.tostat=tostat;
            //printf("min %d ans %d %d\n",min,ans.toplat, ans.tostat);
        }
    }
    return ans;
}
int main(){
    int i;
    int *plat=malloc(20*sizeof(int));
    for(i=0;i<20;i++){
        plat[i]=64;
        //printf("plat[i] %d\n",plat[i] );
    }
    //printf("plat[i] %d\n",plat[0] );
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
            //printf("\n%c\n",target);
            target=fgetc(rptr);
        }
        printf("\ntotalstep :%d\n",totalstep );
    }
    fclose(rptr);
    fclose(wfile);
}
