#include "Diamond.h"

Diamond::Diamond()
{
	Reset();
	sym = 0;
	symb = 220;
	symbol = ( char )symb; //▄
	color = DIAMOND_COLOR;
	diamondResets = 0;
}


Diamond::~Diamond()
{
}


void Diamond::Draw() const
{
	Console::SetCursorPosition( x, y );
	Console::ForegroundColor( color );
	cout << symbol;
}

// Change symbol every 3 frames: '▄' -> '▌' -> '▐' -> '▀'
void Diamond::Update()
{
	symb = 220;
	sym++;
	sym %= 12;
	switch ( sym )
	{
		case 0:
		case 1:
		case 2:
			symb = 220; //▄
			break;
		case 3:
		case 4:
		case 5:
			symb = 221; //▌
			break;
		case 6:
		case 7:
		case 8:
			symb = 222; //▐
			break;
		case 9:
		case 10:
		case 11:
			symb = 223; //▀
			break;
		default:
			break;
	}

	symbol = ( char )symb;
}

void Diamond::Clear() const
{
	Console::SetCursorPosition( x, y );
	cout << ' ';
}

int Diamond::getX() const
{
	return x;
}

int Diamond::getY() const
{
	return y;
}

void Diamond::Reset()
{
	if ( DIAMOND_X_MAX - DIAMOND_X_MIN + 1 != 0 )
		x = rand() % ( DIAMOND_X_MAX - DIAMOND_X_MIN + 1 ) + DIAMOND_X_MIN;
	if ( DIAMOND_Y_MAX - DIAMOND_Y_MIN + 1 != 0 )
		y = rand() % ( DIAMOND_Y_MAX - DIAMOND_Y_MIN + 1 ) + DIAMOND_Y_MIN;
	diamondResets++;
}

void Diamond::Debug( const char *name ) const
{
	cout << name << ".x = " << x << ";     " << endl;
	cout << name << ".y = " << y << ";     " << endl;
	cout << name << ".sym = " << sym << ";     " << endl;
	cout << name << ".symbol = " << symbol << ";     " << endl;
	cout << name << ".diamondResets = " << diamondResets << ";     " << endl;
}

// ☻☺ トニー ☺☻ //