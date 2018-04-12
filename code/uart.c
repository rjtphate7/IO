#include "uart.h"


 void USART_Init( unsigned int ubrr)
 {
	 /* Set baud rate */
	 UBRRH = (unsigned char)(ubrr>>8);
	 UBRRL = (unsigned char)ubrr;
	 /* Enable receiver and transmitter */
	 UCSRB = (1<<RXEN)|(1<<TXEN);
	 /* Set frame format: 8data, 1stop bit */
	 UCSRC = (1<<URSEL)|(3<<UCSZ0);
  	UCSRB|=(1<<RXCIE);
 }

 void USART_Transmit(unsigned char data )
 {
	 /* Wait for empty transmit buffer */
	 while ( !( UCSRA & (1<<UDRE)) );
	 /* Put data into buffer, sends the data */
	 UDR = data;
 }

 unsigned char USART_Receieve ()
 {
	 //when sth is in receieve buffer :)
	 while (!(UCSRA&(1<<RXC)));
	 //pobiera danez tego buforka :)
	 return UDR;
 }

 void USART_Send_Text(char* text)
 {
	 int t=0;
	 while (text[t]!='\0')
	 {
		 USART_Transmit(text[t]);
		 t++;
	 }
 }

 void USART_send_int(int a) //maks liczby 5-cyfrowe
 {
	 char tab[5];
	 int t;
	 int_fast8_t b=0;
	 int z=10000;
	 for (t=5;t>0;t--)
	 {
		 tab[(5-t)]=((a/z)+48);
		 a=(a%z);
		 z/=10;
		 if ((tab[(5-t)])!='0')
		 {
			 USART_Transmit(tab[(5-t)]);
			 b=1;
		 }
		 else
		 {
			 if (b==1)
			 {
				 USART_Transmit(tab[5-t]);
			 }
		 }
	 }

 }
