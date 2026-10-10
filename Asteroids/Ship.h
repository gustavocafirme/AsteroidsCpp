#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "Bullet.h"
#include "Asteroid.h"

class Ship
{
//private:
	Position _scopePosition;
	Position _position;
	Speed _speed;
	static const int MAX_BULLETS = 3;
	Bullet _bullet[MAX_BULLETS];
	int _facing;

	int bulletHitsAsteroid(std::vector<Asteroid>& asteroid, int index);

public:
	Ship();
	void resetShip();

	void newShipFrame(int frame);
	void newBulletsFrame();

	Position getPosition() const;
	Position getScopePosition() const;
	int getFacing() const;
	int getMaxBullets() const;
	Bullet getBullet(int index) const;

	void turnRight();
	void turnLeft();
	void accelerate();

	bool asteroidHitShip(std::vector<Asteroid>& asteroid) const;
	int bulletsHitAsteroid(std::vector<Asteroid>& asteroid);
	int shoot(std::vector<Asteroid>& asteroid);

	bool bulletExists(int index) const;
};

#endif