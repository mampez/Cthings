#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

char *stradd(const char* a, const char* b){

	/*
	 * This function appends two strings (const)
	 * */

    size_t len = strlen(a) + strlen(b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);

    *ret = '\0';
    return strcat(strcat(ret, a) ,b);
    
    
