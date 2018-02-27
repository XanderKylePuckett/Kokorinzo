#pragma once

#include "Enemy.h"

class Diamond
{

	int x;
	int y;
	int sym;
	int symb;
	char symbol;
	short color;

	int diamondResets;

public:
	Diamond();
	~Diamond();

	void Draw() const;
	void Update();
	void Clear() const;
	int getX() const;
	int getY() const;
	void Reset();

	void Debug( const char* ) const;
};

// ☻☺ トニー ☺☻ //