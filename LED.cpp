#include "LED.h"

LED::LED(uint8_t posPin, uint8_t negPin)
{
	this->posPin = posPin;
	this->negPin = negPin;
	status = LOW;
	off();
}

bool LED::getState()
{
	return status;
}

void LED::on()
{
	pinMode(posPin, OUTPUT);
	digitalWrite(posPin, HIGH);
	pinMode(negPin, OUTPUT);
	digitalWrite(negPin, LOW);
	status = true;
}

void LED::off()
{
	digitalWrite(posPin, LOW);
	digitalWrite(negPin, LOW);
}

void LED::toggle()
{
	if (status)
		off();
	else
		on();
}

void LED::blink(unsigned int time, byte rep)
{
	for (byte i = 0; i < rep; i++)
	{
		toggle();
		delay(time / 2);
		toggle();
		delay(time / 2);
	}
}