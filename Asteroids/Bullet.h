#ifndef BULLET_H
#define BULLET_H

#include "Position.h"

class Bullet
{
//private:
	bool _existence;
	Position _position;
	Speed _speed;
	int _remainingFrames;

public:
	Bullet();
	void newBullet(Position shipPosition, int facing);

	void newFrame();

	bool hitAsteroid(Position positionAsteroid);

	bool exists() const;
	Position getPosition() const;
};

#endif