#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
	

uint16_t str_to_decimal(const char *s){
	
	/*
	 * Convert a number string ('3380')
	 * into a uint16_t 0xD34 (3800)
	 * */

    int result = 0;
    for (; *s; ++s) {
        /* Only process recognized digits */
        if (isdigit((unsigned char)*s))
            result = 10 * result + (*s - '0');
    }
    return result;
}
    
    
