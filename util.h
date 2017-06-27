/*
 *
 *  Created on: 3 de abr. de 2017
 *      Author: Manuel (and Jesús)
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <SI_EFM8SB1_Register_Enums.h>                  // SFR declarations
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define ENABLE		1
#define DISABLE 	0

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief
 * Convert a number string ('-0187')
 * into a uint16_t (187 --> 0xBB) an then
 * codify the sign, uint16_t (32955 --> 0x80BB)
 *
 * @param *s, inputLenght
 *
 ******************************************************************************/
uint16_t str_to_decimalSignUc(const char *s, uint8_t inputLength);

/***************************************************************************//**
 * @brief
 * Convert hex number 0x123 into a string '123' avoiding 'sprintf'
 *
 * @param *s, data_in, numChar (uint8--> 2, uint16 --> 4)
 *
 ******************************************************************************/
void num_to_hex_string(char *s, uint16_t data_in, uint8_t numChar); // CODE 0X4F = 79 bytes

/***************************************************************************//**
 * @brief
 * Return string length avoiding 'strlen' function.
 * http://www.stdlib.net/~colmmacc/2009/03/01/optimising-strlen/
 *
 * @param *s
 *
 ******************************************************************************/
size_t my_strlen(const char *s);

/***************************************************************************//**
 * @brief
 * Return pointer avoiding 'strncpy' function.
 * http://www.techiedelight.com/implement-strncpy-function-c/
 *
 * @param char* destination, const char* source, size_t num
 *
 ******************************************************************************/
char* my_strncpy(char* destination, const char* source, size_t num);

/***************************************************************************//**
 * @brief
 * easy memcpy implementation
 * http://www.embedded.com/design/configurable-systems/4024961/Optimizing-Memcpy-improves-speed
 *
 * Reads one byte at a time and writes that byte before reading the next.
 * We'll call this algorithm byte-by-byte.
 *
 * @param void * dst, void const * src, size_t len
 *
 ******************************************************************************/
void * my_memcpy(void * dst, void const * src, size_t len);

/***************************************************************************//**
 * @brief
 * easy memset implementation
 * https://stackoverflow.com/questions/37335181/can-i-implement-memset-memcpy-and-memmove-without-the-c-standard-libraries
 *
 * Write one byte at a time
 *
 * @param void *blk, int c, size_t n
 *
 ******************************************************************************/
void *my_memset(void *blk, char c, size_t n);

/***************************************************************************//**
 * @brief
 * easy strcpy implementation
 * https://stackoverflow.com/questions/14476627/strcpy-implementation-in-c
 *
 * Copy one byte at a time
 *
 * @param char *dest, const char *source
 *
 ******************************************************************************/
void my_strcpy(char *dest, const char *source);

/***************************************************************************//**
 * @brief
 * Own strcat implementation
 * https://codereview.stackexchange.com/questions/40616/pointer-version-of-strcat
 *
 * Copy one byte at a time
 *
 * @param char* dest, const char* source
 *
 ******************************************************************************/
void my_strcat (char* dest, const char* source);

/***************************************************************************//**
 * @brief
 * Compare two strings avoiding 'strcmp' function.
 * https://stackoverflow.com/questions/12136329/how-does-strcmp-work
 *
 * @param *s1, *s2
 *
 ******************************************************************************/
int my_strcmp (const char *s1, const char *s2);

/***************************************************************************//**
 * @brief
 * Reset EFM8
 *
 * @param
 ******************************************************************************/
void resetEFM8 ( void );

#endif /* INC_UTIL_H_ */
