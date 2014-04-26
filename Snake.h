#ifndef SNAKE_H
#define SNAKE_H

#include "LED.h"
#include "List.h"

class Snake
{
private:
	List<LED> snakeLED;
	unsigned int x, y, z;
	uint8_t upButton, downButton,
		frontButton, backButton,
		leftButton, rightButton;
	short int xSpeed, ySpeed, zSpeed;

	inline void resetSpeed();
	
public:
	Snake(
		uint8_t upButton,		uint8_t downButton,
		uint8_t frontButton,	uint8_t backButton,
		uint8_t leftButton,		uint8_t rightButton);
	int getLength() const;
	void move();
};

#endif