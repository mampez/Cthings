#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//-----------------------------------------------------------------------------
// Scripts
//-----------------------------------------------------------------------------

/* 
 * #define TX_BUFFER_LENGTH 25
*/

/*
*	SI_SEGMENT_VARIABLE(tx_buffer[TX_BUFFER_LENGTH], uint8_t, SI_SEG_XDATA);

*	char tempArray[6]={0,0,0,0,0,0};
*	char batArray[6]={0,0,0,0,0,0};
*	char temporal[6]={0,0,0,0,0};
*	int i,j=0;
*
*	sprintf(tempArray, "%x", temperature);
*	sprintf(batArray, "%x", battery);
*
*	//temperature 3 character
*	for(i=0;i<3;i++){
*	   temporal[i]=tempArray[i];
*	}
*
*	//battery 3 character
*	for(j=0;j<2;j++){
*	  temporal[i+j]=batArray[j];
*	}
*
*	strcpy(tx_buffer,"AT$SF=A0900");
*	strncat(tx_buffer,temporal,TX_BUFFER_LENGTH);
*	strncat(tx_buffer,"\r",TX_BUFFER_LENGTH);
*/

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
	
	
int str_to_decimalSign(const char *s) {

	/*
	 * Convert a number string ('-018')
	 * into a signed int 0xffffffee (-18)
	 * */

	int result = 0;
	int sign = 1;

	/*Check sign*/
	if ((unsigned char)*s == '-'){
				sign = -1;
	}

	/*Move pointer*/
	s = s+1;

	for (; *s; ++s) {
		/* Only process recognized digits */
		if (isdigit((unsigned char) *s))
			result = 10 * result + (*s - '0');
	}

	return result * sign;
}
    
