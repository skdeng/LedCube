#ifndef LOCATION_H
#define LOCATION_H

class Location
{
private:
	int x;
	int y;
	int z;

public:
	Location(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z){}
	int getX() const;
	int getY() const;
	int getZ() const;
	friend bool operator==(const Location & l1, const Location & l2); 
	friend bool operator!=(const Location & l1, const Location & l2);
};

#endif