/*
 * servo.h
 *  Created on: 15 Nov 2010
 *      Author: fredrik
 */

#ifndef SERVO_H_
#define SERVO_H_

#define SERVO_PWM PORTC

#define LEFT 1
#define RIGHT 0

// Turn to position pos
void turnPos(int pos);

// Turn to position pos, length lengthUS, delay (after) delayMS
void turn(int pos, int lengthUS, int delayMS);

// Turn n steps
void turnNSteps(unsigned char steps, signed char direction);

// Turns a single step
void turnOneStep(signed char direction);

// Initializing Servo
void initServo( void );

#endif /* SERVO_H_ */
