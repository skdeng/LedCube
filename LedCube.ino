#include "LED.h"

LED l(12,10);

void setup()
{

  /* add setup code here */

}

void loop()
{

  /* add main program code here */
	l.blink(1000, 10);
}
