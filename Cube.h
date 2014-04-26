#ifndef LEDCUBE_H
#define LEDCUBE_H

#include "LED.h"

class Cube
{
private:
	LED ledList[1][1][4] = { { { LED(8, 0), LED(8, 1), LED(8, 2), LED(8, 3); } } };
public:
	Cube();
	void on(short x, short y, short z);
	void off(short x, short y, short z);
	void toggle(short x, short y, short z);
};

#endif