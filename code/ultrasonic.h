#ifndef F_CPU
	#define F_CPU 8000000UL
#endif
//UWAGA! uzywa timera0, przed uzyciem ustawic TRIG(makrodefinicje) i ECHO (wewnatrz funkcji!!)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIG_ON PORTB=(PORTB|1);
#define TRIG_OFF PORTB=(PORTB&(~1));


int ultrasonic_measure();
