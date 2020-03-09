#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CHAR 250
void writeToFile(FILE *in,FILE *out){
	char str[MAX_CHAR];
	while(fgets(str,MAX_CHAR,in) != NULL)
		fputs(str,out);
}
int main(int argc,char *argv[]){
	if(argc <= 2){
		fprintf(stderr,"Not specified input file\n");
		return 0;
	}
	if(argc == 3){
		FILE *p1,*p2,*p3;
		p1 = fopen(argv[1],"r");
		p2 = fopen(argv[2],"r");
		p3 = fopen("myfile.out","w");
		if(p1 == NULL || p2 == NULL || p3 == NULL){
			fprintf(stderr,"Ternimate due to file error\n");
			return 0;
		}
		writeToFile(p1,p3);
		writeToFile(p2,p3);
		fclose(p1);
		fclose(p2);
		fclose(p3);
	}
	else{
		FILE *p[argc - 2],*p3;
		int i = 1;
		p3 = fopen(argv[argc - 1],"w");
		for(;i < (argc - 1);i++){
			p[i - 1] = fopen(argv[i],"r");
			if(p[i - 1] == NULL || p3 == NULL){
				fprintf(stderr,"Ternimate due to file error\n");
				return 0;
			}
			else{
				writeToFile(p[i - 1],p3);
				fclose(p[i - 1]);
			}
		}
		fclose(p3);
	}
	return 0;
}
