#include "Game.h"

void main( void )
{

	bool debug = true;

	for ( ;; )
	{

		Game::StartGame( debug );

		Game *g = new Game();

		for ( ;; )
		{
			Console::Lock( true );
			g->Clear();
			g->Update();
			if ( !g->Draw() )
			{
				break; // Player is dead, Game Over
			}
			Console::Lock( false );
			Sleep( 1000 / FPS );

			// Go to Pause Menu
			if ( GetAsyncKeyState( VK_ESCAPE ) )
			{
				Console::FlushKeys();
				g->Pause();
				Console::Clear();
			}

			// Toggles Debug Mode
			else if ( GetAsyncKeyState( VK_F3 ) )
			{
				Console::FlushKeys();
				if ( g->isSecrets() )
				{
					Console::SetCursorPosition( 0, 0 );
					Console::ResetColor();
					cout << "TOGGLING DEBUG MODE";
					Console::Lock( true );
					Console::BackgroundColor( BACKGROUND );
					Console::Clear();
					g->Debug();
					Sleep( 500 );
				}
			}

			// Enable access to Debug/God Mode
			else if ( GetAsyncKeyState( VK_OEM_3 ) ) // VK_OEM_3 = Grave Accent / Tilde Key
			{
				Console::FlushKeys();
				if ( debug )
				{
					g->Secrets();
					Sleep( 500 );
				}
			}
		}

		if ( g->GameOver() )
		{
			delete g;
			break;
		}
		else
		{
			delete g;
		}
	}

	if ( debug )
	{
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	}
}

// ☻☺ トニー ☺☻ //