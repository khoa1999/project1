#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "helper.h"

#define MAXCHAR 250
#define KEY -50

int main(int argv,char *argc[]){
	FILE *p1,*p2;
	char str[MAXCHAR];
	int max,a,i,j = 0,flag = 1;
	int places[3];
	p1 = fopen(argc[1],"r");
	p2 = fopen("output.txt","w");
	for(i = 0;fgets(str,MAXCHAR,p1) != NULL;i++){
		a = atoi(str);
		if(flag){
			max = a;
			flag = 0;
		}
		else if(max < a)
			max = a;
		if(a == KEY){
			places[++j] = i;
			printf("The key is found at location: %d\n",i);
		}

	}
	printf("The maximum number is %d",max);
}
