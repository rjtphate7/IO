#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void adc_init();
void adc_measure_start(uint8_t channel);
ISR(ADC_vect);
