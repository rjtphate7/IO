/*
 * uart.h
 *
 * Created: 2018-01-31 12:56:07
 *  Author: RealityIsFalse
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>


void USART_Init( unsigned int ubrr);
void USART_Transmit(unsigned char data );
unsigned char USART_Receieve ();
void USART_Send_Text(char* text);
void USART_send_int(int a);

#endif /* UART_H_ */