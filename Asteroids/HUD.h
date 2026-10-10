#ifndef HUD_H
#define HUD_H

#include "Ship.h"

namespace HUD
{
	void printMainScreen();
	void printArrowNewGame();
	void unprintArrowNewGame();
	void printArrowExit();
	void unprintArrowExit();

	void printDifficultySelection();
	void printDifficultyArrowEasy();
	void unprintDifficultyArrowEasy();
	void printDifficultyArrowNormal();
	void unprintDifficultyArrowNormal();
	void printDifficultyArrowHard();
	void unprintDifficultyArrowHard();
	void printDifficultyArrowExtreme();
	void unprintDifficultyArrowExtreme();
	void printDifficultyArrowBack();
	void unprintDifficultyArrowBack();

	void blinkShip(Ship ship, bool* visible);
	void printShip(Ship ship);
	void printBullet(Bullet bullet);
	void printAsteroid(Asteroid asteroid);

	void printInstructionsStart();

	void printDeadShip(Ship ship);
	void printFinalScore(int score);

	void printInstructionsDead();

	void printHUD(int hearts, int score, double fps);
	void refreshHUD(double fps);

	void printHearts(int hearts);
	void printScoreValue(int score);

	void printHelp();

	void printPause();
}

#endif