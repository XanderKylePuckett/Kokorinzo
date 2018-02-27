#pragma once

#include "Define.h"

class Player
{
	double velX, velY;
	double accX, accY;
	int xPos, yPos;

	char symbol;
	short color;

	bool alive;
	bool endGame;

	unsigned short lives;

	bool godMode;

public:
	Player();
	~Player();

	void Draw() const;
	void Update();
	void Clear() const;

	int getP() const;
	int getQ() const;

	bool isAlive() const;
	void die();
	void God( bool );

	void Debug( const char* ) const;

	unsigned short getLives() const;

	void oneUp();

	void EndGame();

private:
	void ResetPlayer();
};

// ☻☺ トニー ☺☻ //