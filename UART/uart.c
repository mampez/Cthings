//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <uart.h>
#include <string.h>

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

// Variables in Interrupts.c
char uart_buffer[UART_BUFFERSIZE];
uint8_t UART_Buffer_Size = 0;
char lastByte = '\0';
uint8_t index = 0;
uint8_t finishTX = 0;
uint8_t finishRX = 0;
uint8_t lenTX = 0;


//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

 char *checkResponse(char *message, bool waitRX, uint8_t responseLength){

	/*Init variables*/
	uint8_t waitUART = 1;
	static char receiveString[UART_BUFFERSIZE] = "";

	/*Max possible response length*/
	if (responseLength > UART_BUFFERSIZE)
		responseLength = UART_BUFFERSIZE;

	if ((responseLength == 0) && (waitRX == true))
		responseLength = 1;

	/*Format the TX data*/
	strncpy(uart_buffer, message, sizeof(uart_buffer) - 1);
	uart_buffer[sizeof(uart_buffer)-1] = '\0';

	/*Calculate the TX data length*/
	lenTX = strlen(message);

	/*Start TX*/
	SCON0_TI = 1;

	/*Wait for a response*/
	while(waitUART){

			//If no response we don't need to wait '\n'!
			if (waitRX == false)
				finishRX = 1;

			if ((finishTX == 1) && (finishRX == 1)){

				/*Restart variables*/
				finishTX = 0;
				finishRX = 0;
				index = 0;
				waitUART = 0;

				if (waitRX == true)
					memcpy(receiveString, uart_buffer, responseLength);

			}//if

	}//while


	/*return an string response*/
	return receiveString;

}


 void checkResponseOK(char *message){

	/*Init variables*/
	uint8_t waitUART = 1;

	/*Format the TX data*/
	strncpy(uart_buffer, message, sizeof(uart_buffer) - 1);
	uart_buffer[sizeof(uart_buffer)-1] = '\0';

	/*Calculate the TX data length*/
	lenTX = strlen(message);

	/*Start TX*/
	SCON0_TI = 1;

	while(waitUART){

			if ( (finishTX == 1) && (finishRX == 1) && (uart_buffer[0] == 'O' && uart_buffer[1] == 'K')){

				//finishRX is 1 when UART detects '\n' as last character

				/*Restart variables*/
				finishTX = 0;
				finishRX = 0;
				index = 0;
				waitUART = 0;

			}//if

	}//while

}

