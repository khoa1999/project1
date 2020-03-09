#include <stdio.h>
#include <math.h>

static inline void swap(char *x,char *y){
	char t = *x;
	*x = *y;
	*y = t;
}
char *reverse(char *buffer,int i,int j){
	while(i < j)
		swap(&buffer[i++],&buffer[j--]);
	return buffer;
}
char *itoa(int value,char *str,int base){
	if(base < 2 || base > 32)
		return str;
	int n = abs(value);

	int i = 0;
	while(n){
		int r = n % base;
		if(r >= 10)
			str[i++] = 65 + (r - 10);//character
		else
			str[i++] = 48 + r;//int
		n = n/base;
	}
	if(i == 0)
		str[i++] = '0';
	if(value < 0 && base == 10)
		str[i++] = '-';
	str[i] = '\0';
	return reverse(str,0,i-1);
}
