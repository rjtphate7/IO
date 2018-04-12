#include "PWM_motors.h"

volatile int8_t left_motor_steering, right_motor_steering;
volatile int8_t counter;


void inline left_motor_forward()
{
	PORTB |= (1<<1);
	PORTB &= ~(1<<2);
}

void inline left_motor_backward()
{
	PORTB &= ~(1<<1);
	PORTB |= (1<<2);
}

void inline left_motor_stop()
{
	PORTB &= ~(1<<1);
	PORTB &= ~(1<<2);
}

void inline right_motor_forward()
{
	PORTD |= (1<<6);
	PORTD &= ~(1<<7);
}

void inline right_motor_backward()
{
	PORTD &= ~(1<<6);
	PORTD |= (1<<7);
}

void inline right_motor_stop()
{
	PORTD &= ~(1<<6);
	PORTD &= ~(1<<7);
}

void PWM_motors_init()
{
	DDRB |= ((1<<1)|(1<<2));
	DDRD |= ((1<<6) | (1<<7));
	PORTB &= ~ ((1<<1)|(1<<2));
	PORTD &= ~ ((1<<6)|(1<<7));	
	left_motor_steering = 0;
	right_motor_steering = 0;
	counter = 0;

	TIMSK |= (1<<TOIE2);
	TCCR2 |= ((1<<CS21)|(1<<CS20));//prescaler 32
}

ISR(TIMER2_OVF_vect)
{
	if (( (left_motor_steering >= 0) ? (left_motor_steering) : (-left_motor_steering)) > counter)
	{
		if ((left_motor_steering & (1<<7)) != 0)
		{
			left_motor_backward();
		}
		else
		{
			left_motor_forward();
		}	
	}
	else
	{
		left_motor_stop();
	}	
	
	if ( ((right_motor_steering >= 0) ? (right_motor_steering) : (-right_motor_steering)) > counter)
	{
		if ((right_motor_steering & (1<<7)) != 0)
		{
			right_motor_backward();
		}
		else
		{
			right_motor_forward();
		}	
	}
	else
	{
		right_motor_stop();
	}

	counter++;

	if (counter >= 101)
	{
		counter = 0;
	}
}

