#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "adc.h"


volatile unsigned char bufor[81];
volatile uint8_t glowa = 0, ogon = 0;
volatile uint_fast16_t sonic = 0;
extern volatile uint8_t adcMeasurements[2];
extern volatile int8_t left_motor_steering, right_motor_steering;
extern volatile int8_t counter;

ISR(USART_RXC_vect) //odbior danych
{
	bufor[glowa]=UDR;
	glowa++;
	if (glowa==80)
	{
		glowa=0;
	}
}

int main(void)
{
	USART_Init(51);
	adc_init();
	PWM_motors_init();

	sei();
	
    	while(1)
	{
		switch (bufor[ogon])
		{
			case 'q':
				USART_send_int(adcMeasurements[0]);
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;
			break;

			case 'w':
				USART_send_int(adcMeasurements[1]);
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;
			break;

			case 'e':
				USART_send_int(adcMeasurements[2]);
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;
			break;

			case 'r':
				USART_send_int(adcMeasurements[3]);
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;
			break;



			case 'n':
				right_motor_steering += 10;
				USART_Transmit('l');				
				USART_send_int(((right_motor_steering >= 0) ? (right_motor_steering) : (-right_motor_steering)));
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;					
			break;
			
			case 'b':
				right_motor_steering -= 10;
				USART_Transmit('l');				
				USART_send_int(((right_motor_steering >= 0) ? (right_motor_steering) : (-right_motor_steering)));			
				USART_Transmit('\n');
				bufor[ogon]='0';
				ogon++;
			break;


			case 'm':
				USART_send_int(ultrasonic_measure());
				USART_Transmit(' ');
				sonic=0;
				bufor[ogon]='0';
				ogon++;
			break;

			case 't':
				USART_Send_Text("doszlo");
				ogon++;
			default:
	    		break;
		}
		if (80 == ogon)
		{
			ogon = 0;
		}
	_delay_ms(10);
    	}
}

