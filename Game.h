#pragma once

#include "Diamond.h"

class Game
{
	unsigned int seed;
	unsigned long long frame;

	Player p;
	Enemy *e1;
	Enemy *e2;
	Diamond d;

	unsigned short score;
	bool debugMode;
	bool secrets;

	public:
	Game();
	~Game();

	bool Draw() const;
	void Update();
	void Clear();

	static void StartGame( bool );

	void Pause();
	bool GameOver();

	void Debug();
	void Secrets();

	bool isSecrets() const;

	private:
	void ShowDebug() const;
	void DrawScore() const;
	void HighScores();
};

// ☻☺ トニー ☺☻ //