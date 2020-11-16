#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
};
int main(){
	struct node a;
	a.data=1;
	printf("%d",a.data);
}
