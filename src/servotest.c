/*
 * servotest.c
 *
 *  Created on: 15 Nov 2010
 *      Author: fredrik
 */

#include "servo.h"
#include "zoidfollow_v1.h"
#include "ad.h"
#include "led.h"
#include "mc.h"
#include "menyFunctions.h"
#include "sw.h"
#include "tweeter.h"
#include "zoidAssert.h"
#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void servotest ( void ) {

	while(1) {

		setAllLeds(0);

		// Escape
		if(SW_2){
			while(SW_2){

			}
			return;
		}

		setMotorLeftPower(power, FORWARD);
		setMotorRightPower(power, FORWARD);

		// Neutral position
		setAllLeds(14);
		turn(100, 1500, 300);

		setAllLeds(12);
		turn(100, 1750, 300);

		setAllLeds(10);
		turn(100, 2000, 300);

		setAllLeds(8);
		turn(100, 1250, 300);

		setAllLeds(6);
		turn(100, 1000, 300);

		setAllLeds(4);
		turn(100, 800, 300);
	}

	return;
}
