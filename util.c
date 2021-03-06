#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char tmp[20] = "";

void gets_(char *buf,int size){
	fgets(buf,size,stdin);
	buf[strlen(buf)-1] = 0;
}

float right_input_float(int func(float), const char *prompt){	// 원하는 값의 input이 입력될 때까지 계속해서 prompt
	float r = 0;												// 입력값은 값을 evaluate하는 함수와 prompt메시지
	while(1){
		gets_(tmp,20);
		if(isalldigit(tmp)){
			r = atof(tmp);
			if(func(r))
				return r;
		}
		printf(prompt);
	}
}

int isalldigit(char str[]){
	if(str[0] == 0)
		return 1;
	else if(str[0] == '.')
		return ispuredigit(&str[1]);
	else if(!isdigit(str[0]))
		return 0;
	else
		return isalldigit(&str[1]);
}

int ispuredigit(char str[]){
	if(str[0] == 0)
		return 1;
	else if(!isdigit(str[0]))
		return 0;
	else
		return ispuredigit(&str[1]);
}

// const char* itoa_(int val){
// 	char *a = malloc(sizeof(char)*20);
// 	a[0] = 0;
// 	int i = 0;
// 	do{
// 		i = val%10;
// 		val = val/10;
// 		strcpy(&a[1],a);
// 		a[0] = i+'0';
// 	}while(val>0);
// 	free(a);
// 	return b;
// }