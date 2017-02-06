#include <uart.h>

//-----------------------------------------------------------------------------
SI_INTERRUPT (UART0_ISR, UART0_IRQn)
{
	   if (SCON0_RI == 1){

		  // If new word is entered
	      if( UART_Buffer_Size == 0){
	    	  index = 0;
	      }

	      // Clear interrupt flag
	      SCON0_RI = 0;

	      // Read a character from UART
	      lastByte = SBUF0;

	      if (UART_Buffer_Size < UART_BUFFERSIZE)
	      {
	    	 //Store in array
	    	  uart_buffer[index] = lastByte;
	         // Update array's size
	         UART_Buffer_Size++;
	         // Update counter
	         index++;
	      }

	      //Wait for '\n' character to finish RX
	      if (lastByte == '\n'){
	    	 finishRX = 1;
	         UART_Buffer_Size = 0;
	      }


	   }
	   if(SCON0_TI == 1)
	   {
		   // Clear interrupt flag
	      SCON0_TI = 0;

		  // If new word is entered
	      if( UART_Buffer_Size == 0){
	    	  index = 0;
	      }

	      // If buffer not empty
	      if (UART_Buffer_Size < lenTX)
	      {

	         // Store a character in the variable byte
	         lastByte = uart_buffer[index];

	         //Transmit by UART
	         SBUF0 = lastByte;
	         //Update counter
	         index++;
	         // Decrease array size
	         UART_Buffer_Size++;

	      }
	      else
	      {
	    	 //Indicate transmission complete
	    	 finishTX = 1;
	         UART_Buffer_Size = 0;
	      }
	   }


}


