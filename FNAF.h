#include "Game.h"
#pragma once

class FNAF {
private:

	/* Program flow flags */
	bool ActiveGame; // Flag: Is the game being played?
	bool ActiveMenu; // Flag: Is the menu being viewed?
	bool ActiveProgram; // Flag: Is the program running?

	/* Data to pass to new constructors of object Gameplay */
	int Level; // Current level player has reached

public:

	/* Constructor */
	FNAF():Level(0), ActiveGame(false), ActiveMenu(false), ActiveProgram(true) {  }
	
	/* Methods */

	void BeginGame() { ActiveGame = true; } // Sets the flag that allows the game to begin

	void EndGame() { ActiveGame = false; } // Sets the flag that allows the game to end

	void EndProgram() { ActiveProgram = false;  } // Sets the flag that allows the program to exit
	
	bool GameStatus() const { return ActiveGame; } // Returns the value of ActiveGame

	bool ProgramStatus() const { return ActiveProgram; } /// Returns the value of ActiveProgram

	bool SpriteTest() { // Draws all sprites numerically and halts program

		for (int i = 0; i <= 94; i++) {

			DrawSprite(i, 0, 0);
			Wait(.2);

		}

		return true;

	}
};

