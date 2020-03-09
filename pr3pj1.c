#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "helper.h"
#define TAB 3
#define MAXLEVEL 4

int main(){
	int curr_level = 0;
	int *mask,array[] = {0,2,2,2,2};
	mask = array;
	while(1){
		char a[5];
		itoa(getpid(),a,10);
		write(1,a,TAB);
		sleep(2);
		if(curr_level < MAXLEVEL){
			int pipefl[2],pipefr[2];
			if(pipe(pipefl) == -1 || pipe(pipefr) == -1){
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
			pid_t left = fork();
			curr_level++;
			if(left == 0){
				char dash[] = "-";
				write(1,dash,sizeof(char));
				close(pipefl[0]);
				read(pipefl[1],mask,sizeof(int)*MAXLEVEL);
			}		
			else if(left == -1){
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			else{	
				mask[curr_level] = 0;
				close(pipefl[1]);
				write(pipefl[0],mask,sizeof(int)*MAXLEVEL);
				waitpid(left,NULL,0);
				pid_t right = fork();
				char cross[] = "~",bar[] = "|",spaces[TAB] = "   ",space[] = " ";
				if(right == 0){
					close(pipefr[0]);
					read(pipefr[1],mask,sizeof(int)*MAXLEVEL);
					int i = 0;
					for(;i < curr_level;i++){
						if(i == (curr_level -1 )){
							write(1,spaces,TAB*sizeof(char));
							write(1,cross,sizeof(char));
						}
						else if(mask[i] == 0){
							write(1,spaces,TAB*sizeof(char));
							write(1,bar,sizeof(char));
						}
						else{
							write(1,spaces,TAB*sizeof(char));
							write(1,space,sizeof(char));
						}
					}
				}
				else if(right == -1){
					perror("fork error");
					exit(EXIT_FAILURE);
				}
				else{	
					mask[curr_level] = 1;
					close(pipefr[1]);
					write(pipefr[0],mask,sizeof(int)*MAXLEVEL);
					waitpid(right,NULL,0);
					exit(EXIT_SUCCESS);
				}
			}
		}
		else{
			char newline[] = "\n";
			write(1,newline,sizeof(char));
			exit(EXIT_SUCCESS);
		}
	}
}
