#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gets_(char *buf,int size);
int isalldigit(char str[]);
int ispuredigit(char str[]);
float right_input_float(int func(float), const char *prompt);
const char* itoa_(int val);