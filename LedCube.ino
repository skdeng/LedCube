/* Author: Shao Kun Deng
 * (c) 2014 under Do Whatever the F You Want With This Code License
 * Credits to White-Tea for code structure
 * @ http://www.instructables.com/id/3D-Snake-on-Charlieplexed-4x4x4-LED-Cube/
 * Corrected some errors and improved/adapted for our project
*/

//Enable debug mode 
// * it's mainly for development anyway
// * but I left thedebugging code cuz teachers always say to show work)
//uncomment this if you want to use debug
//Do not play with this if you simply don't know what debugging is,
//in which case you should not be reading this code anyway
//#define DEBUG

//Enable led testing, basically light up the leds
//Will turn off snake game automatically, don't worry about that :)
//#define LED_TEST

//Initialize button pins
uint8_t upButton	= 0;
uint8_t downButton	= 1;
uint8_t frontButton = 2;
uint8_t backButton	= 3;
uint8_t leftButton  = 4;
uint8_t rightButton = 5;

int buttonThreshold = 50;

//Actual speed of the snake
int speed = 600;

#include "LED.h"
#include "List.h"
#include "Location.h"

//Array of leds for the ledcube (I have no idea why I commented this)
LED* LedCube[4][4][4];
//List of location for the snake
List<Location> Snake;

//Position for the head of the snake
int x, y, z;
//Speed of the snake
int xSpeed, ySpeed, zSpeed;

//Candy variable, will hold the position for candies
Location candy;

//Function forward declarations
void newCandy();
void reset();
inline void resetSpeed() { xSpeed = 0; ySpeed = 0; zSpeed = 0;}

LED l(9, 1);

void setup()
{
	//Jibber-jabber about led pin initialization
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][0][i] = new LED(10+j, i+2);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][1][i] = new LED(i+2, 10 + j);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][2][i] = new LED(10 + j, i + 4);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LedCube[j][3][i] = new LED(i + 4, 10 + j);
		}
	}

	//Set all pins to input for charlieplexing
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

	//(re)Set the game variables
	reset();
	candy = Location(1, 0, 3);
}

void loop()
{
#ifndef LED_TEST
	for (int s = 0; s < speed; s++)
	{
		for (int i = 0; i < Snake.size(); i++)
		{
			LedCube[Snake[i].getX()][Snake[i].getY()][Snake[i].getZ()]->on();
			delay(1);
			LedCube[Snake[i].getX()][Snake[i].getY()][Snake[i].getZ()]->off();
		}
		LedCube[candy.getX()][candy.getY()][candy.getZ()]->on();
		delay(1);
		LedCube[candy.getX()][candy.getY()][candy.getZ()]->off();
	}

	//Movement from inputs, boring stuff, look at your own risk
	if (analogRead(upButton) > buttonThreshold && ySpeed != -1)
	{
		resetSpeed();
		ySpeed = 1;
	}
	else if (analogRead(downButton) > buttonThreshold && ySpeed != 1)
	{
		resetSpeed();
		ySpeed = -1;
	}
	else if (analogRead(leftButton) > buttonThreshold && xSpeed != 1)
	{
		resetSpeed();
		xSpeed = -1;
	}
	else if (analogRead(rightButton) > buttonThreshold && xSpeed != -1)
	{
		resetSpeed();
		xSpeed = 1;
	}
	else if (analogRead(frontButton) > buttonThreshold && zSpeed != -1)
	{
		resetSpeed();
		zSpeed = 1;
	}
	else if (analogRead(backButton) > buttonThreshold && zSpeed != 1)
	{
		resetSpeed();
		zSpeed = -1;
	}

	//Make that the snake stays within the boundaries
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

	//Head of the snake
	Location l = Location(x, y, z);
	if (l != candy)
	{
		Snake.pop_front();
	}
	else
	{
		newCandy();
	}
	//If the snake contains its head (its head has hit the body)
	if (Snake.contains(l))
	{
		//Game over
		int points = Snake.size() + 1;
		//Dislay points using 7-segment display
		reset();
	}
	else
	{
		Snake.push_back(Location(x, y, z));
	}
#endif

	//LED test mode, light up all the leds
#ifdef LED_TEST
	//Light up all the leds for 1sec
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 4; k++)
			{
				LedCube[j][i][k]->on();
			}
		}
	}
	delay(1000);
	//Turn off all the leds for 0.5sec
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				LedCube[j][i][k]->off();
			}
		}
	}
	delay(500);
	//Cycle through each led to check for the connection of each one
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				LedCube[j][i][k]->on();
				delay(100);
				LedCube[j][i][k]->off();
			}
		}
	}
#endif

	//Debug preprocessor block
#ifdef DEBUG
	if (analogRead(5) > 500)
	{
		digitalWrite(7, HIGH);
		resetSpeed();
		xSpeed = -1;
	}
#endif

}

//Generate a new candy at the random location
void newCandy()
{
	candy = Location(random(4), random(4), random(4));
	//If the candy appears on top of the snake, create a new candy
	while (Snake.contains(candy))
	{
		candy = Location(random(4), random(4), random(4));
	}
}

//Reset the game state, a.k.a. restart the game
void reset()
{
	//Empty the snake list
	while (Snake.size() > 0)
	{
		Snake.pop_front();
	}
	//Starting location
	x = 1;
	y = 0;
	z = 0;

	//Starting speed
	xSpeed = 0;
	ySpeed = 0;
	zSpeed = 1;

	Snake.push_back(Location(x, y, z));
	randomSeed(analogRead(5));
	newCandy();
}