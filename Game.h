#include "Header.h"
#pragma once

/* RNG Engine and distributions */
static default_random_engine generator;
static uniform_int_distribution<int> halfandhalf(1, 2);
static uniform_int_distribution<int> FreddyRNG(1, 4); // Freddy RNG
static uniform_int_distribution<int> Freddy_JS_RNG(1, 5); // Freddy's Jumpscare RNG
static uniform_int_distribution<int> BonnieRNG(3, 4); // Bonnie RNG
static uniform_int_distribution<int> ChicaRNG(1, 2); // Chica RNG
static uniform_real_distribution<float> FoxyRNG(.83, 16.67); // Foxy RNG
static uniform_int_distribution<int> GFreddyRNG(1, 100000); // Golden Freddy RNG
static uniform_int_distribution<int> AI_Dist(1, 20); // AI RNG for determining movement

class Game {
private:
	/* Debugging flags */
	const bool FreezePowerDrain = false;
	const bool AlwaysWorkingCamera = false;

	/* Animatronic objects */
	Animatronic Freddy;
	Animatronic Bonnie;
	Animatronic Chica;
	Animatronic Foxy;
	Animatronic GFreddy;

	/* Door Objects */
	Door Left;
	Door Right;

	/* Game data */
	bool GameOver, ShowHelp, NoPower, Win;
	double GameOverTS, GameTS, PowerTS, TransitionTS;
	double CameraErrorTS;
	
	int Camera;
	double PenaltyTS;
	int Usage;
	int Hour;
	double Power;

	bool CameraUp;
	bool CameraError;


	/* Drawing Subroutines */
		/* Rooms */
	void Draw_ShowStage(int x, int y);
	void Draw_BackStage(int x, int y);
	void Draw_Bathrooms(int x, int y);
	void Draw_PirateCove(int x, int y);
	void Draw_PartyRoom(int x, int y);
	void Draw_WestHall(int x, int y);
	void Draw_EastHall(int x, int y);
	void Draw_WestHallCorner(int x, int y);
	void Draw_EastHallCorner(int x, int y);
	void Draw_Kitchen(int x, int y);
	void Draw_Closet(int x, int y);
	void Draw_Office(int x, int y);
		/* Doors */
	void Draw_LeftDoor(int x, int y);
	void Draw_RightDoor(int x, int y);
		/* UI */
	void Draw_Usage(int x, int y);
	void Draw_Power(int x, int y);
	void Draw_Clock(int x, int y);

	/* Animatronic AI Scripts */
	void FreddyAI();
	void BonnieAI();
	void ChicaAI(); 
	void FoxyAI(); 
	void GFreddyAI();

	/* Misc Scripts */
	void BeginGameOver(); // Sets GameOver to true and adds delay to account for jumpscare
	void CheckCameraError(int room, bool & moved); // Check if a camera error should occur
	bool MovementOpportunity(int AI); // Check if an animatronics AI level allows for movement
	void SetFoxyLock(); // Sets foxy lock using RNG
	
	/* Misc Subroutines */
	void PowerLogic(); // Subroutine specifically for power


 public:

	 bool Exit = false; // Exit flag
	 int Night;

	/* Constructor */
	 Game(int Level) {

		 TransitionTS = GetTime();
		 Night = Level;

		 while (GetTimeSince(TransitionTS) < 4) {

			 switch (Night) {

				case 1: DrawSprite(104, 365, 252); break;
				case 2: DrawSprite(105, 365, 252); break;
				case 3: DrawSprite(106, 365, 252); break;
				case 4: DrawSprite(107, 365, 252); break;
				case 5: DrawSprite(108, 365, 252); break;
				case 6: DrawSprite(109, 365, 252); break;
				case 7: DrawSprite(110, 365, 252); break;

			 }

		 }

		 /* Game data */
		 CameraUp = false;
		 CameraError = false;
		 Camera = 1;
		 Usage = 1;
		 GameOver = false;
		 ShowHelp = (Night == 1);
		 CameraErrorTS = 0;
		 NoPower = false;
		 PenaltyTS = GetTime();
		 Hour = 0;
		 GameOverTS = 0;
		 GameTS = GetTime();
		 Power = 99.99;
		 PowerTS = GetTime();
		 Win = false;
		 Exit = false;

		/* AI Levels */
		 switch (Night) {

		 case 1:
			 Freddy.AI = 0;
			 Bonnie.AI = 0;
			 Chica.AI = 0;
			 Foxy.AI = 0;
			 break;

		 case 2:
			 Freddy.AI = 0;
			 Bonnie.AI = 3;
			 Chica.AI = 1;
			 Foxy.AI = 1;
			 break;

		 case 3:
			 Freddy.AI = 1;
			 Bonnie.AI = 0;
			 Chica.AI = 5;
			 Foxy.AI = 2;
			 break;

		 case 4:
			 Freddy.AI = halfandhalf(generator);
			 Bonnie.AI = 2;
			 Chica.AI = 4;
			 Foxy.AI = 6;
			 break;

		 case 5:
			 Freddy.AI = 3;
			 Bonnie.AI = 5;
			 Chica.AI = 7;
			 Foxy.AI = 7;
			 break;

		 case 6:
			 Freddy.AI = 4;
			 Bonnie.AI = 10;
			 Chica.AI = 12;
			 Foxy.AI = 16;
			 break;

		 }

		/* Room positions */
		Freddy.Room = 1;
		Bonnie.Room = 1;
		Chica.Room = 1;
		Foxy.Room = 3;
		GFreddy.Room = 0;

		/* Flags for movement */
		Freddy.Moved = false;
		Bonnie.Moved = false;
		Chica.Moved = false;
		Foxy.Moved = false;

		/* Movement Timestamps */
		Freddy.MoveTS = GetTime();
		Bonnie.MoveTS = GetTime();
		Chica.MoveTS = GetTime();
		Foxy.MoveTS = GetTime();

		/* Freddy Specific Properties */
		Freddy.Lock = false;
		Freddy.Waiting = false;

		/* Bonnie & Chica Specific Properties */
		Bonnie.Scare = false;
		Bonnie.WaitTS = 0;
		Chica.WaitTS = 0;

		/* Foxy Specific Properties */
		Foxy.Stage = 1;
		Foxy.Lock = false;
		Foxy.Waiting = false;
		Foxy.Running = false;
		Foxy.Attempts = 0;
		Foxy.WaitTS = 0;
		Foxy.RunTS = 0;
		Foxy.LockTS = GetTime();
		Foxy.LockDuration = 0;

		/* Golden Freddy Specific Properties */
		GFreddy.Active = false;
		GFreddy.WaitTS = GetTime();
		GFreddy.Waiting = false;
		GFreddy.Stage = 0;

		/* Door properties */
		Left.Lit = false;
		Right.Lit = false;
		Left.Open = true;
		Right.Open = true;
		Left.Broke = false;
		Right.Broke = false;

	};

	/* Primary Routines */
	void Draw();
	void Input();
	void Logic();
};

