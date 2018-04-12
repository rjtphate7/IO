/*
 * ultrasonic.c
 *
 * Created: 2015-08-30 19:07:03
 *  Author: Missman
 */ 


#include "ultrasonic.h"
#define MHzz 8


volatile unsigned int temp=0;


int ultrasonic_measure() //UZYWA TIMERA 0 !!! i trzeba wejscie przerobic!!!(ECHO)
{
	TRIG_ON; //wysoki na TRIG
	_delay_us(10);
	TRIG_OFF; //niski na TRIG
	TIMSK=(TIMSK|1); // ustawienie zezwolenia na przerwania z timera
	while (1)
	{
	if (PIND&(1<<1)) //tutaj czekamy na wzrost napiecia na porcie do ktorego jest podpiete ECHO czujnika
		{
			break;
		}
	}
	TCCR0=0b00000001;//konfig timera
	
	while(1)
	{
		if (!(PINC&(1<<1)))  //tutaj czekamy na spadek napiecia na porcie do ktorego jest podpiete ECHO czujnika
		{
			break;
		}
	}
	temp*=(4.41/MHzz); //wynika ro ze stalych w dokumentacji
	TIMSK=(TIMSK&(~1));//wylaczenie zezwoleniana przerwania z timera
	TCCR0=0b00000000;//wylaczenie timera
	return temp;
}

ISR(TIMER0_OVF_vect) //przerwanie zwiekszajace licznik
{
	temp++;
}
