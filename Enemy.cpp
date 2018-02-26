#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy( int x, int y, int vel )
{
	this->x = x;
	this->y = y;
	this->vel = vel;
	int *symb = new int( 219 );
	symbol = ( char )( *symb ); // '█'
	delete symb;
	color = ENEMY_COLOR;
	active = false;
}

Enemy::~Enemy()
{
}

void Enemy::Draw() const
{
	Console::ForegroundColor( color );
	Console::SetCursorPosition( x, y );
	cout << symbol;
}

void Enemy::Clear() const
{
	Console::SetCursorPosition( x, y );
	cout << ' ';
}

void Enemy::Update( int yPos )
{
	y = ( WINDOW_HEIGHT * yPos / 9 );
	if ( x < 0 )
		x = WINDOW_WIDTH - 1;
	if ( x >= WINDOW_WIDTH )
		x = 0;
	x += vel;
}

void Enemy::Active()
{
	active = true;
}

void Enemy::Inactive()
{
	active = false;
}

bool Enemy::isActive() const
{
	return active;
}

int Enemy::getX() const
{
	return x;
}

int Enemy::getY() const
{
	return y;
}

void Enemy::Debug( const char *name ) const
{
	cout << name << ".x = " << x << ";     " << endl;
	cout << name << ".y = " << y << ";     " << endl;
	cout << name << ".vel = " << vel << ";     " << endl;
	cout << name << ".active = " << active << ";     " << endl;
}

// Increase speed by 1
void Enemy::LevelUp()
{
	if ( vel >= 0 )
		vel++;
	else if ( vel < 0 )
		vel--;
}

// ☻☺ トニー ☺☻ //