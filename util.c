#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char tmp[20] = "";

float right_input_float(int func(float), const char *prompt){	// 원하는 값의 input이 입력될 때까지 계속해서 prompt
	float r = 0;												// 입력값은 값을 evaluate하는 함수와 prompt메시지
	while(1){
		gets(tmp);
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