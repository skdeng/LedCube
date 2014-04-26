#include "Location.h"

int Location::getX() const
{
	return x;
}

int Location::getY() const
{
	return y;
}

int Location::getZ() const
{
	return z;
}

bool operator==(const Location & l1, const Location & l2)
{
	return l1.x == l2.x && l1.y == l2.y && l1.z == l2.z;
}

bool operator!=(const Location & l1, const Location & l2)
{
	return !(l1 == l2);
}