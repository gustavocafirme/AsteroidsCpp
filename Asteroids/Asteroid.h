#ifndef ASTEROID_H
#define ASTEROID_H

#include "Position.h"

class Asteroid
{
//private:
	Position _position[9];
	Speed _speed;
	bool _big;
	static int s_RandAdd;

	void changeRandomSeed();

	int randomPosition(int maxPosition);

	int randomSpeed(int difficulty);

public:
	Asteroid();
	Asteroid(int difficulty);
	Asteroid(int difficulty, Position positionParam);

	void newSpeed(int difficulty);

	void newFrame(int frame);

	void turnSmall(int difficulty);

	bool isBig() const;
	Position getPositionSmall() const;
	Position* getPositionBig();
	Speed getSpeed() const;
};

#endif