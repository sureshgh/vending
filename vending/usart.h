
#include <inttypes.h>

#ifndef USART_H
#define USART_H
/****************************************************************************************************/

#define USART_BAUDRATE 9600	// Baud Rate value
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

//Macros
#define RECEIVE_BUFF_SIZE 256
#define USART_RXC_VECT USART_RXC_vect	//This change from mcu to mcu


#define UBRR_VALUE(baud) ((F_CPU/(baud<<4))-1)


//Varriables
volatile char URBuff[RECEIVE_BUFF_SIZE];	//USART Receive Buffer
volatile int8_t UQFront;
volatile int8_t UQEnd;

//Functions
void USARTInit(uint16_t baudrate);

uint8_t UDataAvailable();
char UReadData();
void UWriteData(char data);
void UWriteString(char *str);
void UWriteCharArray(char *str);
void UFlushBuffer();
void UReadBuffer(void *buff,uint16_t len);

/****************************************************************************************************/


#endif



