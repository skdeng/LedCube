/*
This program was written by WhiteTea and may be altered, used and spread freely
For more information about this program and a tutorial on how to build a 3D Snake Game with LEDs and Arduino, check out following link:
http://www.instructables.com/id/3D-Snake-on-Charlieplexed-4x4x4-LED-Cube/

Instruction to play:
	-Move the snake witht the joystick and push-button
	-The snake cannot move in the direct opposite position of its current position
	-Don't touch the snake and try to eat as much candies as possible
	-When you die, the amount of LEDs burnings is your score
	-To restart, hit one of your buttons (Z-axis)

You might have to change/tweak the following values. I put them in one place and tried to explain what they do.
Also, if you used two push-buttons for your controller (and no Z-axis button on your joystick) you will have to:
	-Uncomment the line in the setup method
	-Add the "== LOW" check to the first Z-axis check in the loop method
	-Add a '!' before the second digitalRead (towards the end of the loop method)
*/

//The boundaries used to check wether the joystick is turned. If your snake reacts too heavy or not at all when moving the joystick, you should tweak these values
int joystickLowerBoundary = 200;
int joystickUpperBoundary = 600;
//Change the joystickX and joystickY values if your snakes goes up/down instead of right/left
int joystickX = 1;
int joystickY = 0;
//Only change these values if you know what your doing :) It will switch the two Z-axis buttons ports, but as
int joystickZ1 = 12;
int joystickZ2 = 13;

//The initial speed (milliseconds) before the snake will move
//If you make this higher, the snake will move slower ==> easier
int initialSpeed = 600;
/*
If this value is 0, no increase in speed will happen when you advance in the game (will always be initialSpeed)
If set to 1, the snake will slightly increase in speed while you eat more candies, starting below the initalSpeed and increasing towards it (never actually reaching it)
The actualSpeed will be given by (initialSpeed*(snakeSize+1-speedIncrease)) / (snakeSize)
Other values will give weird results, but you are free to experiment :)
*/
int speedIncrease = 0;

//The delay (in milliseconds) before a new game starts when the player pressed the Z-axis to restart
int gameDelay = 500;

#include "LED.h"
#include "List.h"
#include "Location.h"

//A  3 dimensional array to keep track of all LEDs
LED* leds[4][4][4];
//A list of Location objects. The snake is determined by all these locations.
List<Location> snake;

//The current location of the snake's head
int x = 0;
int y = 3;
int z = 0;

//The current location of the candy
Location candy;

//The speed the snake travels through the cube with
int xSpeed = 1;
int ySpeed = 0;
int zSpeed = 0;

//forward declaration of the generateNewCandy function
void generateNewCandy();

void setup()
{
	//set the correct leds to the correct ports. If you connected your Cube differently or it doesn't seem to work correctly, you might have to change the numbers below
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			leds[j][0][i] = new LED(8 + j, i);
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			leds[j][1][i] = new LED(i, 8 + j);
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			leds[j][2][i] = new LED(8 + j, i + 4);
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			leds[j][3][i] = new LED(i + 4, 8 + j);
		}
	}
	//the starting location of our snake
	snake.push_back(Location(0, 3, 0));

	//we need the randomSeed to ensure the number generated is really random and not pseudo-random
	randomSeed(analogRead(5));
	//a call to a function that generates a new candy that's on a free position
	generateNewCandy();

	//set all pins to input (needed for charlieplexing)
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
	//uncomment the following line if you have two seperate push-buttons for the Z-axis (not on the joystick)
	//digitalWrite(13, HIGH);
	pinMode(13, INPUT);
	digitalWrite(13, HIGH);
}

void generateNewCandy()
{
	candy = Location(random(4), random(4), random(4));
	while(snake.contains(candy))
	{
		candy = Location(random(4), random(4), random(4));
	}
}

void reset()
{
	while(snake.size() > 0){
		snake.pop_front();
	}
	x = 0;
	y = 3;
	z = 0;
	xSpeed = 1;
	ySpeed = 0;
	zSpeed = 0;
	delay(gameDelay);
	
	snake.push_back(Location(0, 3, 0));
	randomSeed(analogRead(5));
	generateNewCandy();
}

void loop()
{
	for(int i = 0; i < initialSpeed / (snake.size() + 1 - speedIncrease); i++){ 
		for(int j = 0; j < snake.size(); j++){
			leds[snake[j].getX()][snake[j].getY()][snake[j].getZ()]->on();
			delay(1);
			leds[snake[j].getX()][snake[j].getY()][snake[j].getZ()]->off();
		}
		leds[candy.getX()][candy.getY()][candy.getZ()]->on();
		delay(1);
		leds[candy.getX()][candy.getY()][candy.getZ()]->off();
	}
	if(digitalRead(joystickZ1) && ySpeed != -1) //If you have two push-buttons, add the == LOW like below with joystickZ2
	{
		zSpeed = 0;
		ySpeed = 1;
		xSpeed = 0;
	}
	else if(digitalRead(joystickZ2) == LOW && ySpeed != 1)
	{
		zSpeed = 0;
		ySpeed = -1;
		xSpeed = 0;
	}
	else if(analogRead(joystickX) > joystickUpperBoundary && xSpeed != -1)
	{
		xSpeed = 1;
		ySpeed = 0;
		zSpeed = 0;
	}
	else if(analogRead(joystickX) < joystickLowerBoundary && xSpeed != 1)
	{
		xSpeed = -1;
		ySpeed = 0;
		zSpeed = 0;
	}
	else if(analogRead(joystickY) > joystickUpperBoundary && zSpeed != 1)
	{
		zSpeed = -1;
		ySpeed = 0;
		xSpeed = 0;
	}
	else if(analogRead(joystickY) < joystickLowerBoundary && zSpeed != -1)
	{
		zSpeed = 1;
		ySpeed = 0;
		xSpeed = 0;
	}
	if(x + xSpeed == -1)
	{
		x = 3;
	}
	else
	{
		x = (x + xSpeed) % 4;
	}
	if(y + ySpeed == -1)
	{
		y = 3;
	}
	else
	{
		y = (y + ySpeed) % 4;
	}
	if(z + zSpeed == -1)
	{
		z = 3;
	}
	else
	{
		z = (z + zSpeed) % 4;
	}

	Location l = Location(x, y, z);
	if(l != candy)
	{
		snake.pop_front();
	}
	else
	{
		generateNewCandy();
	}
	if(snake.contains(l))
	{
		while(!digitalRead(joystickZ1) && digitalRead(joystickZ2)){ //put a '!' before the second digitalRead if you use two push-buttons (no Z-axis on your joystick)
			int points = snake.size()+1;
			for(int i = 3; i >=0 && points > 0; i--)
			{
				for(int j = 0; j < 4 && points > 0; j++)
				{
					for(int k = 0; k < 4 && points > 0; k++)
					{
						leds[k][i][j]->on();
						delay(1);
						leds[k][i][j]->off();
						points--;
					}
				}
			}
		}
		reset();
	}
	else
	{
		snake.push_back(Location(x, y, z));
	}
}