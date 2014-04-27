/* Author: Shao Kun Deng
 * (c) 2014 under Do Whatever the F You Want With This Code License
 * Credits to White-Tea for code structure
 * @ http://www.instructables.com/id/3D-Snake-on-Charlieplexed-4x4x4-LED-Cube/
 * Code adapted for our project
*/

int initialSpeed = 600;
int speedIncrease = 0;

int gameDelay = 500;

#include "LED.h"
#include "List.h"
#include "Location.h"

LED* LedCube[4][4][4];

List<Location> Snake;

int x, y, z;
int xSpeed, ySpeed, zSpeed;

Location candy;

void newCandy();
void reset();

void setup()
{
	reset();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][0][i] = new LED((i+1)*2, 10+j);
		}
	}
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][1][i] = new LED(i, 8 + j);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][2][i] = new LED(8 + j, i + 4);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][3][i] = new LED(i + 4, 8 + j);
		}
	}*/

	//Snake starting location
	Snake.push_back(Location(0, 3, 0));

	randomSeed(analogRead(5));

	newCandy();

	//Set all pins to input for charlieplexing
	pinMode(0, INPUT);
	pinMode(1, INPUT);
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	pinMode(5, INPUT);
	pinMode(6, INPUT);
	pinMode(7, INPUT);
	pinMode(8, INPUT);
	pinMode(9, INPUT);
	pinMode(10, INPUT);
	pinMode(11, INPUT);
	pinMode(12, INPUT);
	pinMode(13, INPUT);
	digitalWrite(13, HIGH);

}

void loop()
{
	/*for (int i = 0; i < initialSpeed / (Snake.size() + 1 - speedIncrease); i++);
	{
		for (int j = 0; j < Snake.size(); j++)
		{
			LedCube[Snake[j].getX()][Snake[j].getY()][Snake[j].getZ()]->on();
			delay(1);
			LedCube[Snake[j].getX()][Snake[j].getY()][Snake[j].getZ()]->off();
		}
		LedCube[candy.getX()][candy.getY()][candy.getZ()]->on();
		delay(1);
		LedCube[candy.getX()][candy.getY()][candy.getZ()]->off();
	}*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
				LedCube[j][0][i]->on();
		}
	}
}

void newCandy()
{
	candy = Location(random(4), random(4), random(4));
	//If the candy appears on top of the snake, create a new candy
	while (Snake.contains(candy))
	{
		candy = Location(random(4), random(4), random(4));
	}
}

void reset()
{
	while (Snake.size() > 0)
	{
		Snake.pop_front();
	}
	x = 0;
	y = 3;
	z = 0;

	xSpeed = 1;
	ySpeed = 0;
	zSpeed = 0;
	delay(gameDelay);

	Snake.push_back(Location(0, 3, 0));
	randomSeed(analogRead(5));
	newCandy();
}