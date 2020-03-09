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
		if(a == KEY)
			places[++j] = i;

	}
	pid_t pid = fork();
	if(pid == 0){
		char input[MAXCHAR],num1[MAXCHAR],num2[MAXCHAR],num3[MAXCHAR];
		char prefix[MAXCHAR] = "Hi I'm process ";
		char suffix[MAXCHAR] = " and my parent is ";
		char line2[MAXCHAR] = "\nMAX=";
		char newline = '\n';
		strcpy(input,prefix);	
		itoa(getpid(),num1,10);
		strcat(input,num1);
		itoa(getppid(),num2,10);
		strcat(input,suffix);
		strcat(input,num2);
		fputs(input,p2);
		itoa(max,num3,10);
		strcat(line2,num3);
		fputs(line2,p2);
		fputc(newline,p2);
		exit(0);
	}
	else if(pid == -1)
		perror("fork failed");
	else
		waitpid(pid,NULL,WNOHANG);
	for(i = 0;i < 3;i++){
		pid_t pid = fork();
		if(pid == 0){
			char prefix[MAXCHAR] = "\nHi I am process ";
			char suffix[MAXCHAR] = " and I found the hidden key in position A[";
			char bracket = ']';
			char input[MAXCHAR],num1[MAXCHAR],num2[MAXCHAR];
			strcpy(input,prefix);
			itoa(getpid(),num1,10);
			strcat(input,num1);
			strcat(input,suffix);
			itoa(places[i],num2,10);
			strcat(input,num2);
			fputs(input,p2);
			fputc(bracket,p2);
			exit(0);
		}
		else if(pid == -1)
			perror("fork failed");
		else
			waitpid(pid,NULL,WNOHANG);
	}
	fclose(p1);
	fclose(p2);
	return 0;
}
