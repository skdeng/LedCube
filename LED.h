//LED wrapper class
//More intuitive to use

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