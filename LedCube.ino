#include "LED.h"

LED led(13,0);

void setup()
{

  /* add setup code here */
	led.blink(500, 5);
}

void loop()
{
  /* add main program code here */
	led.blink(1000, 1);
}