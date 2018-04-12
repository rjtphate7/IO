#include "adc.h"
#define MAX_NUMBER_OF_INPUTS 2

volatile uint8_t adcMeasurements[MAX_NUMBER_OF_INPUTS];

void adc_init()
{
	DDRC = 0;
	ADMUX &= ~(1<<REFS1);
	ADMUX |= (1<<REFS0);
	ADMUX |= (1<<ADLAR);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADIE);

	ADCSRA |= (1<<ADPS2);
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS0);


	TIMSK |= (1<<TOIE2);// interrupt enabled	

	uint8_t i;
	for (i=0; i < MAX_NUMBER_OF_INPUTS; i++)
	{
		adcMeasurements[i] = 100;
	}
	
	adc_measure_start(0); //start from 0 channel
}

void adc_measure_start(uint8_t channel)
{
	ADMUX &= ~( (1) | (1<<1) | (1<<2) | (1<<3));
	ADMUX |= channel; //selecting channel
	ADCSRA |= (1<<ADSC); //starts conversion
}

ISR(ADC_vect)
{	
	static uint8_t numberOfInput = 0;
	adcMeasurements[numberOfInput] = ADCH;	
	numberOfInput++;	
	adc_measure_start(numberOfInput);
	if (numberOfInput >= MAX_NUMBER_OF_INPUTS)
	{
		numberOfInput = 0;
	}
}
