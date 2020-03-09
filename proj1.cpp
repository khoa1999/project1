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
	FILE *p1,*p2,*p3;
	if(argc <= 2){
		fprintf(stderr,"Not specified input file\n");
		return 0;
	}
	p1 = fopen(argv[1],"r");
	p2 = fopen(argv[2],"r");
	if(argc >= 4)
		p3 = fopen(argv[3],"w");
	else
		p3 = fopen("myfile.out","w");
	if(p1 == NULL || p2 == NULL || p3 == NULL){
		fprintf(stderr,"Ternimate due file error\n");
		return 0;
	}
	writeToFile(p1,p3);
	writeToFile(p2,p3);
	fclose(p1);
	fclose(p2);
	fclose(p3);
	return 0;
}
