//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define UART_BUFFERSIZE        18

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern uint8_t UART_Buffer_Size;
extern char lastByte;
extern char uart_buffer[];
extern uint8_t index;
extern uint8_t finishTX;
extern uint8_t finishRX;
extern uint8_t lenTX;


//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
char *checkResponse(char *message, bool waitRX, uint8_t responseLength);
void checkResponseOK(char *message);
