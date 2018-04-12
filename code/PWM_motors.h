#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void PWM_motors_init();
void PWM_motors_set(uint8_t right, uint8_t left);
ISR(TIMER2_OVF_vect);
