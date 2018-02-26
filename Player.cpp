#include "Player.h"

Player::Player()
{
	ResetPlayer();

	godMode = false;

	endGame = false;

	lives = 3;
	alive = true;
	symbol = '@';
	color = PLAYER_COLOR;
}


Player::~Player()
{
}


void Player::Draw() const
{
	Console::ForegroundColor( color );
	Console::SetCursorPosition( getP(), getQ() );
	cout << symbol;
}

void Player::Update()
{
	if ( GetAsyncKeyState( VK_RIGHT ) || GetAsyncKeyState( 'D' ) )
	{
		Console::FlushKeys();
		accX = 1;
	}
	else if ( GetAsyncKeyState( VK_LEFT ) || GetAsyncKeyState( 'A' ) )
	{
		Console::FlushKeys();
		accX = -1;
	}
	else
	{
		accX = 0;
		if ( yPos < GROUND )
			accX = -1 * velX * FRICTION;
	}

	if ( GetAsyncKeyState( VK_SPACE ) || GetAsyncKeyState( 'W' ) || GetAsyncKeyState( VK_UP ) )
	{
		Console::FlushKeys();
		if ( yPos < GROUND )
		{
			yPos = GROUND;
			velY = JUMP_VELOCITY;
		}
	}

	if ( yPos > 10 )
	{
		accY = -1 * GRAVITY;
	}
	else
	{
		accY = -0.5 * yPos;
	}

	// Update Player position: x = (x0) + (v0) + (1/2)(a)(t^2) .. t=1
	xPos += ( int )( velX + accX / 2 );
	yPos += ( int )( velY + accY / 2 );

	// Update Player velocity: v = (v0) + (a)(t) .. t=1
	velX += accX;
	velY += accY;

	// Bounce off ground
	if ( yPos < 0 )
	{
		yPos *= -1;
		velY *= ( -1.0 * sqrt( BOUNCE / 4.0 ) );
	}

	// Bounce off ceiling
	if ( yPos > PLAYER_YMAX )
	{
		yPos = 2 * PLAYER_YMAX - yPos;
		velY *= ( -1.0 * sqrt( BOUNCE ) );
	}

	// Bounce off left wall
	if ( xPos < 0 )
	{
		xPos *= -1;
		velX *= ( -1.0 * sqrt( BOUNCE ) );
	}

	// Bounce off right wall
	if ( xPos > PLAYER_XMAX )
	{
		xPos = 2 * PLAYER_XMAX - xPos;
		velX *= ( -1.0 * sqrt( BOUNCE ) );
	}

	if ( abs( velX ) < 0.001 )
		velX = 0;
}

void Player::Clear() const
{
	Console::SetCursorPosition( getP(), getQ() );
	cout << ' ';
}

int Player::getP() const
{
	return xPos / 10;
}

int Player::getQ() const
{
	return WINDOW_HEIGHT - yPos / 20 - 1;
}

bool Player::isAlive() const
{
	return alive;
}

void Player::die()
{
	if ( godMode )
		return;

	lives--;

	if ( lives <= 0 || endGame )
	{
		alive = false;
	}
	else
	{
		ResetPlayer();
	}

}

void Player::Debug( const char *name ) const
{
	cout << name << ".velX = " << velX << ";               " << endl;
	cout << name << ".velY = " << velY << ";               " << endl;
	cout << name << ".accX = " << accX << ";               " << endl;
	cout << name << ".accY = " << accY << ";               " << endl;
	cout << name << ".xPos = " << xPos << ";          " << endl;
	cout << name << ".yPos = " << yPos << ";          " << endl;
	cout << name << ".getP() = " << getP() << ";     " << endl;
	cout << name << ".getQ() = " << getQ() << ";     " << endl;
	cout << name << ".alive = " << alive << ";     " << endl;
	cout << name << ".lives = " << lives << ";     " << endl;
}

void Player::God( bool god )
{
	godMode = god;
}

void Player::ResetPlayer()
{
	velX = 0;
	velY = 0;
	accX = 0;
	accY = 0;
	xPos = rand() % PLAYER_XMAX;
	yPos = PLAYER_YMAX;
}

void Player::oneUp()
{
	lives++;
}

unsigned short Player::getLives() const
{
	return lives;
}

void Player::EndGame()
{
	endGame = true;
	alive = false;
}

// ☻☺ トニー ☺☻ //