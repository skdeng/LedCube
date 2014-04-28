/*
||
|| @file LED.h
|| @version 1.1
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making/using LEDs
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

/* Approved by Shao Kun Deng
 * It does make things easier :D
*/

#ifndef LED_H
#define LED_H

#include "Arduino.h"

class LED
{
public:
	LED(uint8_t posPin, uint8_t negPin);
	bool getState();
	void on();
	void off();
	void toggle();

	void blink(unsigned int time, byte times = 1);

private:
	bool status;
	uint8_t posPin;
	uint8_t negPin;
};

#endif