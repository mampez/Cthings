/*
 *
 *  Created on: 3 de abr. de 2017
 *      Author: Manuel (and Jesús)
 */


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8SB1_Register_Enums.h>
#include <util.h>

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
uint16_t str_to_decimalSignUc(const char *s, uint8_t inputLength){

	/*
	 * Convert a number string ('-0187')
	 * into a uint16_t (187 --> 0xBB) an then
	 * codify the sign, uint16_t (32955 --> 0x80BB)
	 */

	uint16_t result = 0;
	uint8_t digitIndex = 0;
	bool sign = false;

	/*Check Sign*/
	if ((unsigned char)*s == '-'){
		sign = true;
		s = s+1;
		digitIndex = digitIndex + 1;
	}

	for (; *s; ++s) {
		/* Only process recognized digits */
		if ((isdigit((unsigned char) *s)) && (digitIndex < inputLength)){
			result = 10 * result + (*s - '0');
			digitIndex = digitIndex + 1;
		}
	}

	if (sign == true)
		result = 0x8000 + result;

	return result;

}

void num_to_hex_string(char *s, uint16_t data_in, uint8_t numChar){ // CODE 0X4F = 79 bytes
    uint8_t i;
    char *p = s+numChar;
    char aux;

    *p-- = 0;
    for (i = 0 ; i<numChar ; i++) {
        aux = (char)(data_in & 0x000f) + '0';
        if (aux > '9')
            aux += 'a' - '0' -10;
        *p-- = aux;
        data_in = data_in >> 4;
    }
}

char* my_strncpy(char* destination, const char* source, size_t num)
{

	/*
	 * strncpy version which copies byte-to-byte
	 */

	// take a pointer pointing to the beginning of destination string
	char* ptr = destination;

	// return if no memory is allocated to the destination
	if (destination == NULL)
		return NULL;

	// copy first num characters of C-string pointed by source
	// into the array pointed by destination
	while (*source && num--)
	{
		*destination = *source;
		destination++;
		source++;
	}

	// null terminate destination string
	*destination = '\0';

	// destination is returned by standard strncpy()
	return ptr;
}

void my_strcpy(char *dest, const char *source)
{
	/*
	 * strcpy version which copies byte-to-byte
	 */
    do{
	        *dest++ = *source;
	    }while(*source++ != '\0');
}


int my_strcmp (const char *s1, const char *s2) {

	/*
	 * Each character is compared in turn an a decision
	 * is made as to whether the first or second string is greater, based on that character.
	 * Only if the characters are identical do you move to the next character and,
	 * if all the characters were identical, zero is returned.
	 *
	 */
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;

        p1++;
        p2++;
    }

    if (*p2 != '\0') return -1;

    return 0;
}

void *my_memcpy(void * dst, void const * src, size_t len)
{
	/*
	 * Reads one byte at a time and writes that byte before reading the next.
	 */

    char * pDst = (char *) dst;
    char const * pSrc = (char const *) src;

    while (len--)
    {
        *pDst++ = *pSrc++;
    }

    return (dst);
}

void *my_memset(void *blk, char c, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i)
        ((char *) blk)[i] = c;
    return blk;
}

void my_strcat (char* dest, const char* source)
{
	/*
	 * strcat version which join strings byte-to-byte
	 */

  while(*dest != '\0') /* finding the end of the string */
  {
    dest++;
  }

  *dest = *source;
  while(*dest != '\0')
  {
    dest++;
    source++;
    *dest = *source;
  }
}

size_t my_strlen(const char * s)
{
	/*
	 * strlen with pointers
	 */

   char * ptr;

   for (ptr = s; *ptr; ++ptr);

   /*Return length*/
   return ptr - s;
}


void resetEFM8(){

	*((uint8_t SI_SEG_DATA *)0x00) = 0xA5;
	RSTSRC = 0x12; //SWRSF, PORSF

}
