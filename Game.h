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
	bool GameOver, ToggleHelp, NoPower;
	double GameOverTS, GameTS, PowerTS;
	double CameraErrorTS;
	
	int Camera;
	double PenaltyTS;
	int Usage;
	int Hour;
	double Power;
	int Night;

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
	/* Constructor */
	 Game() :CameraUp(false), CameraError(false), Camera(1), Usage(1), GameOver(false), 
		 Power(2.99), GameOverTS(0), GameTS(GetTime()), PowerTS(GetTime()), Night(7), Hour(0),
		 ToggleHelp(false), CameraErrorTS(0), NoPower(false), PenaltyTS(GetTime()) {
		/* AI Levels */
		Freddy.AI = 0;
		Bonnie.AI = 0;
		Chica.AI = 0;
		Foxy.AI = 0;

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

		/* Door properties */
		Left.Lit = false;
		Right.Lit = false;
		Left.Open = true;
		Right.Open = true;
		Left.Broke = false;
		Right.Broke = false;

		ToggleHelp = (Night > 1); // Help will only force itself to appear on Night 1
	};

	/* Primary Routines */
	void Draw();
	void Input();
	void Logic();
};

