#pragma once
#include <string.h>
#include <stdlib.h>

char* alloc_str_copy(char* str){
	char* copy = (char*) malloc(sizeof(char) * (strlen(str) + 1));
	copy[0]='\0';
	strcpy(copy, str);
	return copy;
}