#include "Game.h"
#pragma once

class FNAF {
private:

	/* Program flow flags */
	bool ActiveGame; // Flag: Is the game being played?
	bool ActiveMenu; // Flag: Is the menu being viewed?

	/* Data to pass to new constructors of object Gameplay */
	int Level; // Current level player has reached

public:

	/* Objects */
	Game Gameplay;

	/* Constructor */
	FNAF():Level(0), ActiveGame(false), ActiveMenu(false) {  }
	
	/* Methods */
	void BeginGame() { ActiveGame = true; } // Sets the flag that allows the game to begin
	
	bool GameStatus() const { return ActiveGame; } // Returns the value of ActiveGame

	bool SpriteTest() { // Draws all sprites numerically and halts program

		for (int i = 0; i <= 94; i++) {

			DrawSprite(i, 0, 0);
			Wait(.2);

		}

		return true;

	}
};

