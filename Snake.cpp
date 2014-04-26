#include "Snake.h"

void Snake::resetSpeed()
{
	xSpeed = 0;
	ySpeed = 0;
	zSpeed = 0;
}

Snake::Snake(
	uint8_t upButton,		uint8_t downButton,
	uint8_t frontButton,	uint8_t backButton,
	uint8_t leftButton,		uint8_t rightButton
	):
	upButton(upButton),			downButton(downButton),
	frontButton(frontButton),	backButton(backButton),
	leftButton(leftButton),		rightButton(rightButton)
{
	x = 0;	y = 3;	z = 0;
	xSpeed = 1;
	ySpeed = 0;
	zSpeed = 0;
}

int Snake::getLength() const
{
	return snakeLED.size();
}

void Snake::move()
{
	//Ajust the speed according to the inputs
	if (digitalRead(rightButton) == HIGH)
	{
		resetSpeed();
		xSpeed = 1;
	}
	else if (digitalRead(leftButton) == HIGH)
	{
		resetSpeed();
		xSpeed = -1;
	}
	else if (digitalRead(upButton) == HIGH)
	{
		resetSpeed();
		ySpeed = 1;
	}
	else if (digitalRead(downButton) == HIGH)
	{
		resetSpeed();
		ySpeed = -1;
	}
	else if (digitalRead(frontButton) == HIGH)
	{
		resetSpeed();
		zSpeed = 1;
	}
	else if (digitalRead(backButton) == HIGH)
	{
		resetSpeed();
		zSpeed = -1;
	}

	//Make sure that the snake is within the cube boundary
	if (x + xSpeed == -1)	
	{
		x = 3;
	}
	else
	{
		x = (x + xSpeed) % 4;
	}
	if (y + ySpeed == -1)
	{
		y = 3;
	}
	else
	{
		y = (y + ySpeed) % 4;
	}
	if (z + zSpeed == -1)
	{
		z = 3;
	}
	else
	{
		z = (z + zSpeed) % 4;
	}
}