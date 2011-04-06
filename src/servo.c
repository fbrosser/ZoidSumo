/*
 * servo.c
 *
 *  Created on: 15 Nov 2010
 *      Author: fredrik
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "eeprom.h"
#include "servo.h"
#include "led.h"
#include "servo.h"

int servoPos;

// Turn to position
void turnPos(int pos) {
	SERVO_PWM = pos;
	OCR1A = pos;
	OCR1B = pos;
	OCR1B |= (pos<<8);
}

void turn(int pos, int lengthUS, int delayMS) {
	turnPos(pos);
	_delay_us(lengthUS);
	turnPos(0);
	_delay_ms(delayMS);
}

// Turn a single step
void turnOneStep(signed char direction) {

}

// Initializing Servo
void initServo( void ) {

	// clear previous register values
	TCCR1A = 0;
	TCCR1B = 0;
	//TIFR1 = 0;

	// Fast PWM
	// Top ICR1
	// Set A on compare match
	// Prescaler1 8
	// Output PB2
	DDRB |= (1<<PB2);
	DDRC |= (1<<PC5);
  	TCCR1A |= (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B |= (1<<CS11) | (1<<WGM12) | (1<<WGM13);
	ICR1 = 20000;
}

