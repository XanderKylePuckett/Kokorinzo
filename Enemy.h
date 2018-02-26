#pragma once

#include "Player.h"

class Enemy
{
	int x;
	int y;
	int vel;
	short color;
	char symbol;
	bool active;

	public:
	Enemy( int, int, int );
	~Enemy();

	void Draw() const;
	void Clear() const;
	void Update( int );
	void Debug( const char* ) const;

	void Active();
	void Inactive();
	bool isActive() const;
	int getX() const;
	int getY() const;

	void LevelUp();

	Enemy();
};

// ☻☺ トニー ☺☻ //