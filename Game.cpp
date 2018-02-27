#include "Game.h"

Game::Game()
{
	Console::EOLWrap( false );
	Console::BackgroundColor( BACKGROUND );
	Console::CursorVisible( false );

	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;

	Console::SetWindowSize( width, height );
	Console::SetBufferSize( width, height );

	srand( ( unsigned int )time( 0 ) );
	rand();
	seed = rand() * rand() / rand() + rand() - rand();
	srand( seed );
	rand();

	Console::Clear();
	e1 = new Enemy( ENEMY_1_X, ENEMY_1_Y, ENEMY_1_X_VEL );
	e2 = new Enemy( ENEMY_2_X, ENEMY_2_Y, ENEMY_2_X_VEL );

	score = 0;
	debugMode = false;
	secrets = false;

	frame = 0;
}

Game::~Game()
{
	delete e1;
	delete e2;
}

void Game::StartGame( bool debug )
{
	Console::BackgroundColor( BACKGROUND );
	Console::ForegroundColor( Cyan );
	Console::Clear();
	cout << "Gameplay:" << endl;
	cout << "Get the blue thingy, avoid the red things" << endl;
	cout << endl;
	cout << "4 Blue things = 1 extra life" << endl;
	cout << "10 Blue things = increase speed of red things" << endl;
	cout << endl;
	cout << "Controls:" << endl;
	cout << "Right: D or right arrow" << endl;
	cout << "Left:  A or left arrow" << endl;
	cout << "Jump: Space or W or Up Arrow" << endl;
	if ( debug )
		cout << "Enable Cheats: Grave Accent / Tilde Key" << endl << endl;
	system( "pause" );
	PlaySound( TEXT( "song.wav" ), NULL, SND_FILENAME | SND_ASYNC );
}

bool Game::Draw() const
{
	if ( !p.isAlive() )
		return false;

	if ( debugMode )
	{
		ShowDebug();
	}

	p.Draw();

	if ( !e1->isActive() && !e2->isActive() )
		return true;

	d.Draw();
	e1->Draw();
	e2->Draw();

	DrawScore();

	return true;
}

void Game::Update()
{
	frame++;

	p.Update(); // Update Player
	e1->Update( E1_U ); // Update first Enemy
	e2->Update( E2_U ); // Update second Enemy
	d.Update(); // Update Gem

	// Set enemies visible when player first hits the ground
	if ( ( !e1->isActive() || !e2->isActive() ) && p.getQ() >= WINDOW_HEIGHT - 1 )
	{
		e1->Active();
		e2->Active();
	}

	// Player picks up the Gem
	if ( ( e1->isActive() && e2->isActive() ) &&
		( p.getP() >= d.getX() - RADIUS && p.getP() <= d.getX() + RADIUS ) &&
		 ( p.getQ() >= d.getY() - RADIUS && p.getQ() <= d.getY() + RADIUS ) )
	{
		// Increment score by 1
		score++;

		// Player gets extra life for every 4th Gem pickup
		if ( score % 4 == 0 )
			p.oneUp();

		// Enemy velocities increase by 1 for every 10th Gem pickup
		if ( score % 10 == 0 )
		{
			e1->LevelUp();
			e2->LevelUp();
		}

		// Sets new position for the Gem
		d.Reset();
	}

	// Player gets hit by Enemy 1 or Enemy 2
	if ( ( e1->isActive() &&
		( p.getP() >= e1->getX() - RADIUS && p.getP() <= e1->getX() + RADIUS ) &&
		 ( p.getQ() >= e1->getY() - RADIUS && p.getQ() <= e1->getY() + RADIUS ) ) ||

		 ( e2->isActive() &&
		 ( p.getP() >= e2->getX() - RADIUS && p.getP() <= e2->getX() + RADIUS ) &&
		 ( p.getQ() >= e2->getY() - RADIUS && p.getQ() <= e2->getY() + RADIUS ) ) )
	{
		// Player loses a life and resets
		p.die();

		// Sets enemies invisible and resets the Gem
		if ( p.getLives() > 0 && !debugMode )
		{
			e1->Inactive();
			e2->Inactive();
			d.Reset();
		}
	}

}

void Game::Clear()
{
	Sleep( 5 );

	p.Clear();

	if ( e1->isActive() || e2->isActive() )
	{
		e1->Clear();
		e2->Clear();
		d.Clear();
	}

	if ( width != WINDOW_WIDTH || height != WINDOW_HEIGHT )
	{
		width = WINDOW_WIDTH;
		height = WINDOW_HEIGHT;
		Console::SetBufferSize( width, height );
		d.Reset();
		Console::BackgroundColor( BACKGROUND );
		Console::Clear();
	}
}

void Game::Pause()
{
	Console::BackgroundColor( BACKGROUND );
	Console::Clear();
	Console::SetCursorPosition( WINDOW_WIDTH / 2 - 3, WINDOW_HEIGHT / 2 );
	Console::ForegroundColor( DIAMOND_COLOR );
	cout << "PAUSE";
	Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT * 2 / 3 );
	cout << "Press Enter to continue" << endl;
	if ( secrets )
	{
		Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT * 2 / 3 + 1 );
		Console::ForegroundColor( DarkMagenta );
		cout << "Press 0 to toggle ";
		if ( debugMode )
			cout << "off";
		else
			cout << "on";
		cout << " Debug Mode / God Mode";
	}
	Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT * 2 / 3 + 2 );
	Console::ForegroundColor( DarkRed );
	cout << "Press q to end or restart the game";
	Sleep( 500 );
	for ( ;; )
	{
		if ( GetAsyncKeyState( VK_RETURN ) )
		{
			Console::FlushKeys();
			return;
		}
		else if ( GetAsyncKeyState( '0' ) )
		{
			Console::FlushKeys();
			if ( secrets )
			{
				Debug();
				return;
			}
		}
		else if ( GetAsyncKeyState( 'Q' ) )
		{
			Console::FlushKeys();
			if ( debugMode )
			{
				Debug();
			}

			p.EndGame();
			return;
		}
	}
}

bool Game::GameOver()
{
	Console::Lock( true );
	Console::Clear();
	DrawScore();
	Console::SetCursorPosition( WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 );
	Console::ForegroundColor( DIAMOND_COLOR );
	cout << "GAME OVER!";
	Console::Lock( false );
	PlaySound( NULL, NULL, SND_FILENAME | SND_ASYNC );
	Sleep( 400 );
	Console::Lock( true );
	Console::SetCursorPosition( WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 + 1 );
	cout << "Thank you for playing " << GAMENAME;
	Console::Lock( false );
	HighScores();
	Sleep( 600 );
	Console::SetCursorPosition( WINDOW_WIDTH / 2 - 9, WINDOW_HEIGHT / 2 + 2 );
	cout << "Play Again? (y/n)";
	for ( ;; )
	{
		if ( GetAsyncKeyState( 'Y' ) )
		{
			Console::FlushKeys();
			return false;
		}
		else if ( GetAsyncKeyState( 'N' ) )
		{
			Console::FlushKeys();
			break;
		}
	}

	if ( secrets )
	{
		Console::SetCursorPosition( WINDOW_WIDTH / 2 - 14, WINDOW_HEIGHT / 2 + 3 );
		system( "pause" );
		Console::Lock( true );
		Console::BackgroundColor( Black );
		for ( int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++ )
			cout << ( char )( rand() % 26 + 'a' );
		Console::SetCursorPosition( rand() % ( WINDOW_WIDTH - 20 ), rand() % WINDOW_HEIGHT );
		Console::BackgroundColor( Red );
		Console::ForegroundColor( Black );
		cout << "TONY WAS HERE!! >:D";
		Console::ResetColor();
		Sleep( 50 );
		Console::SetCursorPosition( 0, 0 );
		Console::Lock( false );
		Sleep( 400 );
	}

	Console::Lock( false );
	Sleep( 50 );

	system( "cls" );
	Console::CursorVisible( true );

	Console::EOLWrap( true );

	return true;
}

void Game::DrawScore() const
{
	if ( p.isAlive() )
	{
		Console::SetCursorPosition( WINDOW_WIDTH / 3 - 15, WINDOW_HEIGHT / 10 );
		Console::ForegroundColor( DIAMOND_COLOR );
		cout << "Press Esc to enter Pause Menu";
		if ( secrets )
		{
			Console::SetCursorPosition( WINDOW_WIDTH / 3 - 15, WINDOW_HEIGHT / 10 + 1 );
			Console::ForegroundColor( DIAMOND_COLOR | FOREGROUND_INTENSITY );
			cout << "Press F3 to toggle God Mode";
		}
	}

	if ( debugMode )
	{
		Console::ForegroundColor( Magenta );
		Console::DrawBox( WINDOW_WIDTH / 3 * 2 - 27, WINDOW_HEIGHT / 10 + 2, 23, 3, true );
		Console::SetCursorPosition( WINDOW_WIDTH * 2 / 3 - 26, WINDOW_HEIGHT / 10 + 3 );
		cout << "DEBUG MODE / GOD MODE";
		Console::SetCursorPosition( WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT / 10 + 3 );
		Console::ForegroundColor( DIAMOND_COLOR );
		cout << "Score: " << score;
		Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 + 4 );
		cout << "Lives: " << p.getLives();
	}
	else
	{
		Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 + 3 );
		Console::ForegroundColor( DIAMOND_COLOR );
		cout << "Score: " << score;
		Console::SetCursorPosition( WINDOW_WIDTH / 3, WINDOW_HEIGHT / 10 + 4 );
		cout << "Lives: " << p.getLives();
	}
}

void Game::Debug()
{
	debugMode = !debugMode;
	if ( !debugMode )
	{
		p.God( false );
	}
	else
	{
		p.God( true );
	}
}

void Game::ShowDebug() const
{
	Console::ForegroundColor( Black );
	Console::BackgroundColor( BACKGROUND | FOREGROUND_INTENSITY );
	Console::SetCursorPosition( 0, 0 );
	cout << "Seed: " << seed << ";     " << endl;
	cout << "Frame: " << frame << ";     " << endl;
	cout << "Size: " << width << "x" << height << ";     " << endl;
	p.Debug( "p" );
	e1->Debug( "e1" );
	e2->Debug( "e2" );
	d.Debug( "d" );
}

void Game::Secrets()
{
	secrets = !secrets;
	if ( debugMode )
		Debug();
	Console::BackgroundColor( BACKGROUND );
	Console::Lock( true );
	Console::Clear();
}

bool Game::isSecrets() const
{
	return secrets;
}

void Game::HighScores()
{

}

// ☻☺ トニー ☺☻ //