#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "sw.h"
#include "ad.h"
#include "irDist.h"
#include "defines.h"
#include "mc.h"
#include "eeprom.h"
#include <avr/motorPwr.h>
#include "Zoidbergsumo.h"

// Sumo main
int sumoMain() {

	unsigned char dir;
 	unsigned char delay = 10;
	unsigned char i;

	// Default Motor Power
	unsigned char motorPwr = 100;	
	
	// 8 MHz, default
	clock_prescale_set(0);

	// Init
	initMotorcontrollers();
	initLed();
	initSw();
	initTweeter();
	initAd();
	initIr();

	// Allow global interrups
	sei();
	sensorSensitivity = DEFAULT_EDGE;
	SenseEdge = DEFAULT_SENSOR;

	// Hold 5 seconds on startup
	setAllLeds(0);

	// Wait for start
	while(!SW_1){}		

	// Countdown...
	for(int i=1; i<5; i++) {
		_delay_ms(1000);
		setAllLeds(i);
	}
	
	// ...Go!

	while(1) {
				
		// Front Left Sensor detects edge
		if(edge(SENSOR_LEFT) && !edge(SENSOR_RIGHT)) {

			setLed(DIODE_4, ON);

			// Turn left
			dir = LEFT;

			// Turn
			setMotorRightmotorPwr(motorPwr, REVERSE);
			setMotorLeftmotorPwr(motorPwr * 2, REVERSE);

			// Delay for turning
			for(i = 0; i < delay; i++) {
				_delay_ms(200);
			}

			setLed(DIODE_4,OFF);
		}

		// Front Right Sensor detects edge
		if(edge(SENSOR_RIGHT) && !edge(SENSOR_LEFT)) {

			setLed(DIODE_1, ON);

			// Turn right
			dir = RIGHT;

			// Turn
			setMotorRightmotorPwr(motorPwr * 2, REVERSE);
			setMotorLeftmotorPwr(motorPwr, REVERSE);

			// Delay for turning
			for(i = 0; i<delay; i++) {
				_delay_ms(200);
			}

			setLed(DIODE_1,OFF);
		}

		// Both Front Reflex Sensors detect edge
		if(edge(SENSOR_RIGHT) && edge(SENSOR_LEFT)) {

			setLed(DIODE_4, ON);
			setLed(DIODE_1, ON);

			// Turn right
			dir = RIGHT;

			// Turn
			setMotorRightmotorPwr(motorPwr * 2, REVERSE);
			setMotorLeftmotorPwr(motorPwr * 2, REVERSE);

			// Delay for turning
			for(i = 0; i < delay + 1; i++) {
				_delay_ms(200);
			}

			setLed(DIODE_1,OFF);
			setLed(DIODE_4,OFF);
		}

		// No danger of going overboard: check for opponent
		else {
			// Robot dead ahead!
			if(irRecLeft && irRecRight) {

				// Set both LEDs
				setLed(DIODE_2,ON);
				setLed(DIODE_3,ON);

				// Set full speed ahead!
				setMotorRightmotorPwr(motorPwr * 2, FORWARD);
				setMotorLeftmotorPwr(motorPwr * 2, FORWARD);
			}

			// Turn Right
			else if(irRecRight) {

				// Set only right LED
				setLed(DIODE_2,ON);
				setLed(DIODE_3,OFF);

				// Reverse right, forward left
				dir = RIGHT;
				setMotorRightmotorPwr(motorPwr * 2, REVERSE);
				setMotorLeftmotorPwr(motorPwr * 2, FORWARD);

			}

			// Turn Left
			else if(irRecLeft) {

				// Set only left LED
				setLed(DIODE_2,OFF);
				setLed(DIODE_3,ON);

				// Reverse left, forward right
				dir = LEFT;
				setMotorRightmotorPwr(motorPwr * 2, FORWARD);
				setMotorLeftmotorPwr(motorPwr * 2, REVERSE);
			}

			// Search for enemy robot (No detections)
			else {

				// Both LEDs OFF
				setLed(DIODE_2,OFF);
				setLed(DIODE_3,OFF);

				// Where did we last see the other robot...?
				if(dir == RIGHT) {
					setMotorRightmotorPwr(motorPwr * 2, REVERSE);
					setMotorLeftmotorPwr(motorPwr * 2, FORWARD);
				}
				else {
					setMotorRightmotorPwr(motorPwr * 2, FORWARD);
					setMotorLeftmotorPwr(motorPwr * 2, REVERSE);
				}
			}
		}
	}

	return 0;
}
