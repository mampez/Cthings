/******************************************************************************
 * Copyright (c) 2017 Jesús Ibañez and Manuel Menchaca
 *
 * C functions (very useful!)
 *****************************************************************************/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8SB1_Register_Enums.h>
#include <util.h>

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
int my_isdigit(char c) {

	/*
	 *	Function:  my_isdigit
	 * ------------------------------------------------------------------------
	 *
	 * Checks if the passed character is a decimal digit character.
	 *
	 *  Arguments:
	 *  - c = This is the character to be checked.
	 *  - inputLength = number of characters to be copied
	 *
	 *  Return:
	 *  - Returns non-zero value if c is a digit, else it returns 0.
	 *
	 */

    return (c >= '0') && (c <= '9');
}


uint16_t string_to_hexInt(const char *s, uint8_t inputLength)
{
	/*
	 *	Function:  string_to_hexInt
	 * ------------------------------------------------------------------------
	 *
	 * Convert ASCII number (string) into an "encoded" hex uint16_t
	 *
	 *  We'll encode the sign with 0x8000 + abs(result)
	 *
	 *
	 *  Arguments:
	 *  - s = pointer to the string to be compared
	 *  - inputLength = number of characters to be copied
	 *
	 *  Return:
	 *  - result = uint16_t with the codified string and also sign bit
	 *
	 *  Examples:
	 *  - '-0187' --> 0x80BB
	 *	- '187' --> 0x00BB
	 */

	// Variable definition
	uint16_t result = 0;
	uint8_t digitIndex = 0;
	bool sign = false;

	// Check sign
	if ((unsigned char)*s == '-') {
		sign = true;
		s = s+1;
		digitIndex = digitIndex + 1;
	}
	// Process only recognized digits
	for (; *s; ++s) {
		if ((my_isdigit((unsigned char) *s)) && (digitIndex < inputLength)) {
			result = 10 * result + (*s - '0');
			digitIndex = digitIndex + 1;
		}
	}
	// Encode the sign with 0x8000
	if (sign == true)
		result = 0x8000 + result;
	return result;
}

void int_to_hexString(const char *s, uint16_t data_in, uint8_t numChar)
{
	/*
	 *	Function:  int_to_hexString
	 * ------------------------------------------------------------------------
	 * Convert uint16_t into an ASCII string
	 *
	 *  Arguments:
	 *  - s = pointer to the output string
	 *  - data_in = input number (uint16_t)
	 *  - numChar = number of characters to be copied
	 *  			*uint8  - 2
	 *  			*uint16 - 4
	 *
	 *  Return:
	 *  - Nothing
	 *
	 *  Examples:
	 *  - 0x6A   --> '6A'
	 *  - 0x3344 --> '3344'
	 */

	// Variable definition
    uint8_t i;
    char *p = s+numChar;
    char aux;

    *p-- = 0;
    for (i = 0 ; i<numChar ; i++) {
        aux = (char)(data_in & 0x000f) + '0';
        if (aux > '9')
            aux += 'a' - '0' - 10;
        *p-- = aux;
        data_in = data_in >> 4;
    }
}

uint16_t hexString_to_int(const char *s) {

	/*
	 *	Function:  hexString_to_int
	 * ------------------------------------------------------------------------
	 * Convert hex string to int
	 *
	 *  Arguments:
	 *  - s = pointer to the input hex string
	 *
	 *  Return:
	 *  - uint16 conversion
	 *
	 *  Examples:
	 *  - "234567"   --> 0x4567
	 *  - "A1" --> 0xA1
	 *  - "1234"   --> 0x1234
	 */

	// Variable definition
	char *p;
	char c;
	uint16_t value = 0;
	uint8_t n = 0;
	uint8_t i;

	p = s;
	while (*p++ != 0) {    // finds the length of the input string
		n++;
	}
	if (n > 4) {    // n is the number of chars to be converted (4 maximum)
		n = 4;
	}
	p -= n + 1;    // now p points to the most significant char to be converted

	for (i = 0 ; i < n ; i++ ) {
		value = value << 4;
		c = *p++;
		//Convert
		if (c <= '9') {
			c = c - '0';
		}
		else if (c <= 'F') {
			c = c - 'A' + 10;
		}
		else {
			c = c - 'a' + 10;
		}
		value += (uint16_t)c ;
	}
	return value;
}


char* my_strncpy(char* destination, const char* source, size_t num)
{
	/*
	 * Function:  my_strncpy
	 * ------------------------------------------------------------------------
	 * Implementation of strncpy
	 *
	 * Copies up to num characters from the string pointed to,
	 * by source to destination
	 *
	 *  Arguments:
	 *  - destination = pointer to the output string
	 *  - source = input number (uint16_t)
	 *  - num = number of characters to be copied from source
	 *
	 *  Return:
	 *  -Final copy of the copied string.
	 *
	 */

	// take a pointer pointing to the beginning of destination string
	char* ptr = destination;

	// return if no memory is allocated to the destination
	if (destination == NULL)
		return NULL;

	// copy first num characters of C-string pointed by source
	// into the array pointed by destination
	while (*source && num--) {
		*destination = *source;
		destination++;
		source++;
	}
	// null terminate destination string
	*destination = '\0';
	return ptr;
}

void my_strcpy(char *destination, const char *source)
{
	/*
	 *	Function:  my_strcpy
	 * ------------------------------------------------------------------------
	 *
	 * Implementation of strcpy
	 *
	 * Copies the string pointed to, by source to destination.
	 *
	 *  Arguments:
	 *  - destination = pointer to the output
	 *  - source = This is the string to be copied.
	 *
	 *  Return:
	 *  - Nothing
	 *
	 */

    do{
	    *destination++ = *source;
	}while(*source++ != '\0');
}

int my_strcmp (const char *s1, const char *s2)
{
	/*
	 * 	 Function:  my_strcmp
	 * ------------------------------------------------------------------------
	 *
	 * 	Implementation of strcmp
	 *
	 * 	Compares the string pointed to, by s1 to the string pointed to by s2.
	 *
	 *  Arguments:
	 *  - s1 = pointer to the first string to be compared
	 *  - s2 = to the second string to be compared
	 *
	 *  Return:
	 *  - if Return value < 0 then it indicates s1 is less than s2.
	 *  - if Return value > 0 then it indicates s2 is less than s1.
	 *  - if Return value = 0 then it indicates s1 is equal to s2.
	 *
	 */

	// Variable definition
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0') {
        if (*p2 == '\0')
        	return  1;
        if (*p2 > *p1)
        	return -1;
        if (*p1 > *p2)
        	return  1;
        //Increment pointers
        p1++;
        p2++;
    }
    if (*p2 != '\0')
    	return -1;
    return 0;
}

char* my_strstr(char *str, char *substr)
{
	/*
	 *	Function:  my_strstr
	 * ------------------------------------------------------------------------
	 *
	 * 	Implementation of strstr
	 *
	 * 	Finds the first occurrence of the substring in the string.
	 * 	NOTE: The terminating '\0' characters are not compared.
	 *
	 *  Arguments:
	 *  - str = pointer to the string which will be scanned
	 *  - substr = pointer to the string which will be searched
	 *
	 *  Return:
	 *
	 *  - firstOccurrence = pointer to the first occurrence of any of the
	 *                      entire sequence of characters specified in
	 *                      substr.
	 *
	 *  - NULL pointer means substr is not in str
	 *
	 */

	while (*str) {
		char *firstOccurrence = str;
		char *substring = substr;
		// If first character of sub string match, check for whole string
		while (*str && *substring && *str == *substring) {
			  str++;
			  substring++;
		}
		// If complete sub string match, return starting address
		if (!*substring)
			return firstOccurrence;
		// Increment main string
		str = firstOccurrence + 1;
	}
	return NULL;
}

void *my_memcpy(void * dst, void const * src, size_t len)
{
	/*
	 *	Function:  my_memcpy
	 * ------------------------------------------------------------------------
	 *
	 * 	Implementation of memcpy
	 *
	 * 	Copies len characters from  src to dst.
	 *
	 *  Arguments:
	 *  - dst = pointer to the destination array where the content is to be copied
	 *  - src = pointer to the source of data to be copied
	 *  - len = the number of bytes to be copied.
	 *
	 *  Return:
	 *  - Nothing
	 */

    // Variable definition
    char * pDst = (char *) dst;
    char const * pSrc = (char const *) src;

    while (len--) {
        *pDst++ = *pSrc++;
    }
    return (dst);
}

void *my_memset(void *str, char c, size_t n)
{
	/*
	 *	Function:  my_memset
	 * ------------------------------------------------------------------------
	 *
	 * 	Implementation of memset
	 *
	 * 	Copies the character c to the first n characters of
	 * 	the string pointed to, by the argument str.
	 *
	 *  Arguments:
	 *  - str = pointer to the block of memory to fill.
	 *  - c = Value to be set.
	 *  - n = the number of bytes to be set to the value.
	 *
	 *  Return:
	 *  - Nothing
	 */

	// Variable definition
    size_t i;

    for (i = 0; i < n; ++i)
        ((char *) str)[i] = c;

    return str;
}

void my_strcat (char* destination, const char* source)
{
	/*
	 *	Function:  my_strcat
	 * ------------------------------------------------------------------------
	 * 	Implementation of strcat
	 *
	 *  Appends the string pointed to by source
	 *  to the end of the string pointed to by destination.
	 *
	 *  Arguments:
	 *  - destination = pointer to the destination string
	 *  - source = pointer to the string to be appended.
	 *
	 *  Return:
	 *  - Nothing
	 */

	//Find the end of the string
	while(*destination != '\0') {
		destination++;
	}
	*destination = *source;

	while(*destination != '\0') {
		destination++;
		source++;
		*destination = *source;
	 }
}

size_t my_strlen(const char * s)
{
	/*
	 *	Function:  my_strlen
	 * ------------------------------------------------------------------------
	 * 	Implementation of strlen
	 *
	 *  Returns the length of the string s.
	 *  NOTE: Not including the terminating null character.
	 *
	 *  Arguments:
	 *  - s = pointer to the string whose length is to be found.
	 *
	 *  Return:
	 *  - return the string length
	 */

	// Variable definition
	char * ptr;

	for (ptr = s; *ptr; ++ptr);

	return ptr - s;
}

void resetEFM8()
{
	/*
	 *	Function:  resetEFM8
	 * ------------------------------------------------------------------------
	 * 	Reset the EFM8SB
	 *
	 *  Arguments:
	 *  -Nothing
	 *
	 *  Return:
	 *  - Nothing
	 */

	*((uint8_t SI_SEG_DATA *)0x00) = 0xA5;
	RSTSRC = 0x12; // SWRSF, PORSF
}
