#include "Game.h"
#include "FNAF.h"

void Game::Draw() {

		/* Rooms */
		Draw_BackStage(10, 78);
		Draw_ShowStage(279, 10);
		Draw_PartyRoom(122, 78);
		Draw_Bathrooms(652, 122);
		Draw_WestHall(221, 360);
		Draw_EastHall(459, 360);
		Draw_WestHallCorner(221, 518);
		Draw_EastHallCorner(459, 518);
		Draw_Kitchen(579, 360);
		Draw_Closet(109, 420);
		Draw_PirateCove(36, 247);
		Draw_Office(341, 533);

		/* Doors */
		Draw_LeftDoor(315, 579);
		Draw_RightDoor(433, 579);

		/* HUD */
		Draw_Usage(7, 610);
		Draw_Power(7, 631);
		Draw_Clock(777, 15);

		/* Help */
		if (!ShowHelp)
			DrawSprite(99, 563, 542);
		else
			DrawSprite(100, 563, 542);

}

void Game::Input() {

	if (!GameOver && !Win && GetConsoleWindow() == GetForegroundWindow() && !NoPower) {

		if (KeyIsDown(32, true, false)) {

			CameraUp = !CameraUp;
			Left.Lit = Right.Lit = false;

			if (Camera == 2 && Bonnie.Room == 2 && AI_Dist(generator) <= 5)
				Bonnie.Scare = true;

			if (CameraUp && !Foxy.Lock) {

				Foxy.Lock = true;
				SetFoxyLock();

			}

		}

		if (KeyIsDown(37, true, false) && CameraUp)
			Camera--;

		if (KeyIsDown(39, true, false) && CameraUp)
			Camera++;

		if (KeyIsDown('A', true, false) && !CameraUp) {

			Left.Lit = !Left.Lit;
			if (Right.Lit)
				Right.Lit = false;

		}

		if (KeyIsDown('D', true, false) && !CameraUp) {

			Right.Lit = !Right.Lit;
			if (Left.Lit)
				Left.Lit = false;

		}
		if (KeyIsDown('Q', true, false) && !CameraUp && !Left.Broke)
			Left.Open = !Left.Open;

		if (KeyIsDown('E', true, false) && !CameraUp && !Right.Broke)
			Right.Open = !Right.Open;
		
		if (KeyIsDown('H', true, false))
			ShowHelp = !ShowHelp;

		if (KeyIsDown('C', true, true) && KeyIsDown('D', true, true) && KeyIsDown('0', true, true))
			Hour = 6;

		/* Numpad specific controls */
			if (KeyIsDown(103, true, false) && CameraUp)
				Camera = 2;

			if (KeyIsDown(104, true, false) && CameraUp)
				Camera = 1;

			if (KeyIsDown(105, true, false) && CameraUp)
				Camera = 5;

			if (KeyIsDown(100, true, false) && CameraUp)
				Camera = 3;

			if (KeyIsDown(101, true, false) && CameraUp)
				Camera = 4;

			if (KeyIsDown(102, true, false) && CameraUp)
				Camera = 9;

			if (KeyIsDown(97, true, false) && CameraUp)
				Camera = 6;

			if (KeyIsDown(98, true, false) && CameraUp)
				Camera = 7;

			if (KeyIsDown(99, true, false) && CameraUp)
				Camera = 8;

			if (KeyIsDown(96, true, false) && CameraUp)
				Camera = 10;

			if (KeyIsDown(110, true, false) && CameraUp)
				Camera = 11;
	}

}

void Game::Logic() {


	if (!GameOver && !NoPower) {

		FreddyAI();
		BonnieAI();
		ChicaAI();
		FoxyAI();
		GFreddyAI();

	}

	if (CameraUp && Bonnie.Room == 2 && Bonnie.Scare)
		Bonnie.Scare = true;
	else
		Bonnie.Scare = false;

	if (Camera < 1)
		Camera = 1;
	if (Camera > 11)
		Camera = 11;

	Usage = !Left.Open + !Right.Open + CameraUp + Left.Lit + Right.Lit + 1;

	if (!FreezePowerDrain)
		PowerLogic();

	if (GameOver && GetTimeSince(GameOverTS) > 1.3) {

		Exit = true;

	}

	if (Hour == 6) {

		Win = Exit = true;
		TransitionTS = GetTime();
		system("CLS");

		while (GetTimeSince(TransitionTS) < 4)
			DrawSprite(111, 385, 252);

	}

	if (GetTimeSince(CameraErrorTS) > 4.6 && CameraError)
		CameraError = false;

	if (Power <= 0) {

		if (!NoPower) {

			Freddy.Room = 14;
			Freddy.Stage = 0;
			Freddy.Waiting = false;
			Left.Open = true, Right.Open = true, Left.Lit = false, Right.Lit = false;
			Freddy.WaitTS = GetTime();
			NoPower = true;
			CameraUp = false;

		}

		if ((GetTimeSince(Freddy.WaitTS) > 5.00)) {

			Freddy.Stage++;
			Freddy.WaitTS = GetTime();

			if (Freddy.Room == 14 && Freddy_JS_RNG(generator) == 1) {

				Freddy.Room = 12;
				Freddy.Stage = 0;
				Freddy.WaitTS = GetTime();

			}

			else if (Freddy.Room == 12 && Freddy_JS_RNG(generator) == 2) {

				Freddy.Room = 15;
				Freddy.Stage = 0;
				Freddy.WaitTS = GetTime();
				Freddy.Waiting = true;

			}

		}

		if (Freddy.Stage == 4 && Freddy.Room == 14 && !Freddy.Waiting) {

			Freddy.Stage = 0;
			Freddy.Room = 12;
			Freddy.WaitTS = GetTime();

		}

		else if (Freddy.Stage == 4 && Freddy.Room == 12 && !Freddy.Waiting) {

			Freddy.Stage = 0;
			Freddy.Room = 15;
			Freddy.WaitTS = GetTime();
			Freddy.Waiting = true;

		}

		else if (Freddy.Waiting && GetTimeSince(Freddy.WaitTS) > 2) {

			Freddy.WaitTS = GetTime();

			if (Freddy_JS_RNG(generator) == 1) {

				BeginGameOver();
				Freddy.Room = 13;
				Freddy.Waiting = false;

			}

		}

	}

	if (GFreddy.Stage == 0 && Hour == 2) {

		GFreddy.Stage++;
		Bonnie.AI++;

	}

	else if (GFreddy.Stage == 1 && Hour == 3) {

		GFreddy.Stage++;
		Bonnie.AI++;
		Chica.AI++;
		Foxy.AI++;

	}

	else if (GFreddy.Stage == 2 && Hour == 4) {

		GFreddy.Stage++;
		Bonnie.AI++;
		Chica.AI++;
		Foxy.AI++;

	}

}

void Game::Draw_BackStage(int x, int y) {
	if (Camera == 2 && CameraUp) {

		if (CameraError)
			DrawSprite(10, x, y);

		else if (Bonnie.Room == 2 && Bonnie.Scare)
			DrawSprite(12, x, y);

		else if (Bonnie.Room == 2)
			DrawSprite(11, x, y);

		else
			DrawSprite(9, x, y);

	}

	else 
		DrawSprite(8, x, y);

}

void Game::Draw_ShowStage(int x, int y) {
	if (Camera == 1 && CameraUp) {

		if (CameraError)
			DrawSprite(3, x, y);

		else if (Bonnie.Room == 1 && Freddy.Room == 1 && Chica.Room == 1)
			DrawSprite(7, x, y);

		else if (Bonnie.Room == 1 && Freddy.Room == 1)
			DrawSprite(5, x, y);

		else if (Chica.Room == 1 && Freddy.Room == 1)
			DrawSprite(6, x, y);

		else if (Freddy.Room == 1)
			DrawSprite(4, x, y);

		else
			DrawSprite(2, x, y);

	}

	else
		DrawSprite(1, x, y);

}

void Game::Draw_PartyRoom(int x, int y) {

	if (Camera == 4 && CameraUp) {

		if (CameraError)
			DrawSprite(26, x, y);

		else if (Chica.Room == 4 && Bonnie.Room == 4)
			DrawSprite(30, x, y);

		else if (Bonnie.Room == 4)
			DrawSprite(29, x, y);

		else if (Chica.Room == 4)
			DrawSprite(28, x, y);

		else if (Freddy.Room == 4)
			DrawSprite(27, x, y);

		else
			DrawSprite(25, x, y);

	}

	else
		DrawSprite(24, x, y);

}

void Game::Draw_Bathrooms(int x, int y) {

	if (Camera == 5 && CameraUp) {

		if (CameraError)
			DrawSprite(15, x, y);

		else if (Chica.Room == 5)
			DrawSprite(17, x, y);

		else if (Freddy.Room == 5)
			DrawSprite(16, x, y);

		else
			DrawSprite(14, x, y);

	}

	else
		DrawSprite(13, x, y);

}

void Game::Draw_Office(int x, int y) {

	if (NoPower && Freddy.Room == 13)
		DrawSprite(112, x, y);

	else if (NoPower)
		DrawSprite(103, x, y);

	else if (!CameraUp && GFreddy.Room == 13)
		DrawSprite(62, x, y);

	else if (!CameraUp && Bonnie.Room != 13 && Chica.Room != 13 && Freddy.Room != 13 && Foxy.Room != 13)
		DrawSprite(57, x, y);

	else if (CameraUp && Bonnie.Room != 13 && Chica.Room != 13 && Freddy.Room != 13 && Foxy.Room != 13)
		DrawSprite(56, x, y);

	else if (Bonnie.Room == 13)
		DrawSprite(58, x, y);

	else if (Chica.Room == 13)
		DrawSprite(59, x, y);

	else if (Freddy.Room == 13)
		DrawSprite(60, x, y);

	else if (Foxy.Room == 13)
		DrawSprite(61, x, y);

}

void Game::Draw_LeftDoor(int x, int y) {

	if (Left.Open) {

		if (Freddy.Room == 12)
			DrawSprite(80, x, y);

		else if (Bonnie.Room == 12 && Left.Lit && !CameraUp)
			DrawSprite(79, x, y);

		else if (Left.Broke && !CameraUp && Left.Lit)
			DrawSprite(77, x, y);

		else if (Left.Lit && !CameraUp)
			DrawSprite(81, x, y);

		else
			DrawSprite(75, x, y);

	}

	else {

		if (Bonnie.Room == 12 && Left.Lit && !CameraUp)
			DrawSprite(85, x, y);

		else if (Left.Lit && !CameraUp)
			DrawSprite(82, x, y);

		else
			DrawSprite(76, x, y);


	}

}
void Game::Draw_RightDoor(int x, int y) {

	if (Right.Open) {

		if (Chica.Room == 12 && Right.Lit && !CameraUp)
		DrawSprite(78, x, y);

		else if (Right.Broke && !CameraUp && Right.Lit)
			DrawSprite(77, x, y);

		else if (Right.Lit && !CameraUp)
			DrawSprite(81, x, y);

		else
			DrawSprite(75, x, y);
	}

	else {
		if (Chica.Room == 12 && Right.Lit && !CameraUp)
			DrawSprite(84, x, y);

		else if (Right.Lit && !CameraUp)
			DrawSprite(83, x, y);

		else
			DrawSprite(76, x, y);
	}

}

void Game::Draw_WestHall(int x, int y) {

	if (Camera == 7 && CameraUp) {

		if (CameraError)
			DrawSprite(33, x, y);

		else if (Foxy.Room == 7)
			DrawSprite(35, x, y);

		else if (Bonnie.Room == 7)
			DrawSprite(34, x, y);

		else
			DrawSprite(32, x, y);
	}

	else
		DrawSprite(31, x, y);

}

void Game::Draw_EastHall(int x, int y) {

	if (Camera == 8 && CameraUp) {

		if (CameraError)
			DrawSprite(38, x, y);

		else if (Chica.Room == 8)
			DrawSprite(39, x, y);

		else if (Freddy.Room == 8)
			DrawSprite(40, x, y);

		else
			DrawSprite(37, x, y);

	}

	else
		DrawSprite(36, x, y);

}

void Game::Draw_WestHallCorner(int x, int y) {

	if (Camera == 10 && CameraUp) {

		if (CameraError)
			DrawSprite(48, x, y);

		else if (GFreddy.Active)
			DrawSprite(102, x, y);

		else if (Bonnie.Room == 10)
			DrawSprite(51, x, y);

		else
			DrawSprite(47, x, y);

	}

	else 
		DrawSprite(46, x, y);

}
void Game::Draw_EastHallCorner(int x, int y) {

	if (Camera == 11 && CameraUp) {

		if (CameraError)
			DrawSprite(48, x, y);

		else if (Chica.Room == 11)
			DrawSprite(49, x, y);

		else if (Freddy.Room == 11)
			DrawSprite(50, x, y);

		else
			DrawSprite(47, x, y);

	}

	else
		DrawSprite(46, x, y);

}

void Game::Draw_Kitchen(int x, int y) {

	if (Camera == 9 && CameraUp) {

		if (Chica.Room == 9)
			DrawSprite(43, x, y);

		else if (Freddy.Room == 9)
			DrawSprite(44, x, y);

		else
			DrawSprite(45, x, y);
	}

	else 
		DrawSprite(42, x, y);

}

void Game::Draw_Closet(int x, int y) {

	if (Camera == 6 && CameraUp) {

		if (CameraError)
			DrawSprite(54, x, y);

		else if (Bonnie.Room == 6)
			DrawSprite(55, x, y);

		else
			DrawSprite(53, x, y);

	}

	else
		DrawSprite(52, x, y);

}

void Game::Draw_PirateCove(int x, int y) {

	if (Camera == 3 && CameraUp) {

		if (CameraError)
			DrawSprite(19, x, y);

		else if (Foxy.Room == 3 && Foxy.Stage == 1)
			DrawSprite(22, x, y);

		else if (Foxy.Room == 3 && Foxy.Stage == 2)
			DrawSprite(21, x, y);

		else if (Foxy.Room == 3 && Foxy.Stage == 3)
			DrawSprite(20, x, y);

		else
			DrawSprite(23, x, y);

	}

	else
		DrawSprite(18, x, y);

}

void Game::Draw_Usage(int x, int y) {

	DrawSprite(69 + Usage, x, y);

}

bool Game::MovementOpportunity(int AI) {

	return (AI_Dist(generator) <= AI);

}

void Game::FreddyAI() {

	if (GetTimeSince(Freddy.MoveTS) > 3.02) {

		Freddy.MoveTS = GetTime();

		if (MovementOpportunity(Freddy.AI) && !Freddy.Waiting && !Freddy.Lock) {

			Freddy.Waiting = true;
			Freddy.LockTS = GetTime();

		}

		if (!Freddy.Lock && GetTimeSince(Freddy.LockTS) > (16.67 - 1.67 * Freddy.AI) && Freddy.Waiting) {

			Freddy.Moved = true;
			CheckCameraError(Freddy.Room, Freddy.Moved);
			Freddy.Waiting = false;

			if (Freddy.Room == 1 && Chica.Room != 1 && Bonnie.Room != 1)
				Freddy.Room = 4;

			else if (Freddy.Room == 4)
				Freddy.Room = 5;

			else if (Freddy.Room == 5)
				Freddy.Room = 9;

			else if (Freddy.Room == 9)
				Freddy.Room = 8;

			else if (Freddy.Room == 8)
				Freddy.Room = 11;

			else if (Freddy.Room == 11 && Right.Open) {

				Freddy.Room = 14;
				Freddy.WaitTS = GetTime();
			}

			else if (Freddy.Room == 11 && !Right.Open)
				Freddy.Room = 8;

			Freddy.Moved = true;
			CheckCameraError(Freddy.Room, Freddy.Moved);

		}

	}

	if (Freddy.Room == 14 && !CameraUp && GetTimeSince(Freddy.WaitTS) > 1 && Freddy.AI != 0) {

		Freddy.WaitTS = GetTime();

		if (FreddyRNG(generator) == 1) {

			Freddy.Room = 13;
			BeginGameOver();

		}

	}

	if (CameraUp && Freddy.Room != 11)
		Freddy.Lock = true;

	else if ((Camera == 11 && CameraUp && Freddy.Room == 11) || (!CameraUp && Freddy.Room == 11))
		Freddy.Lock = true;

	else
		Freddy.Lock = false;

}

void Game::GFreddyAI() {

	if (Camera == 10 && CameraUp && GFreddyRNG(generator) == 1 && GetTimeSince(GFreddy.WaitTS) > 1 && !GFreddy.Active && !GFreddy.Waiting) {

		GFreddy.Active = true;
		GFreddy.Room = 10;

	}

	else if (GetTimeSince(GFreddy.WaitTS) > 1 && !GFreddy.Active && !GFreddy.Waiting)
		GFreddy.WaitTS = GetTime();
	
	else if (GFreddy.Active && !CameraUp) {

		GFreddy.WaitTS = GetTime();
		GFreddy.Waiting = true;
		GFreddy.Active = false;
		GFreddy.Room = 13;

	}

	else if (GFreddy.Waiting && CameraUp) {

		GFreddy.Waiting = false;
		GFreddy.Room = 0;
		GFreddy.WaitTS = GetTime();

	}

	else if (GetTimeSince(GFreddy.WaitTS) > 4 && GFreddy.Waiting)
		abort();

}

void Game::FoxyAI() {

	if (GetTimeSince(Foxy.LockTS) > Foxy.LockDuration && !CameraUp && Foxy.Lock)
		Foxy.Lock = false;

	if (GetTimeSince(Foxy.MoveTS) > 5.01 && !Foxy.Waiting && !Foxy.Running) {

		Foxy.MoveTS = GetTime();

		if (MovementOpportunity(Foxy.AI) && !Foxy.Lock && (GetTimeSince(Foxy.LockTS) > Foxy.LockDuration))
			Foxy.Stage++;

		if (Foxy.Stage == 4) {

			Foxy.Room = 7;
			Foxy.WaitTS = GetTime();
			Foxy.Waiting = true;
			Foxy.Stage = halfandhalf(generator);

		}

	}

	if (Foxy.Waiting) {

		if ((CameraUp && Camera == 7) || GetTimeSince(Foxy.WaitTS) > 25) {

			Foxy.Running = true;
			Foxy.RunTS = GetTime();
			Foxy.Waiting = false;

		}

	}
	if (Foxy.Running && (GetTimeSince(Foxy.RunTS) > 2)) {

		Foxy.Running = false;

		if (Left.Open) {

			Foxy.Room = 13;
			BeginGameOver();

		}

		else {

			Foxy.Room = 3;
			Power -= 1 + (5.0 * Foxy.Attempts);
			Foxy.Attempts++;

		}

	}

}

void Game::ChicaAI() {

	if (GetTimeSince(Chica.MoveTS) > 4.98) {

		Chica.MoveTS = GetTime();

		if (MovementOpportunity(Chica.AI)) {

			int t = ChicaRNG(generator);

			Chica.Moved = true;
			CheckCameraError(Chica.Room, Chica.Moved);

			if (Chica.Room == 1)
				Chica.Room = 4;

			else if (Chica.Room == 4) {

				if (t == 1)
					Chica.Room = 5;

				else
					Chica.Room = 9;

			}

			else if (Chica.Room == 5) {
				
				if (t == 1)
					Chica.Room = 9;

				else
					Chica.Room = 4;

			}

			else if (Chica.Room == 9) {
				
				if (t == 1)
					Chica.Room = 8;

				else
					Chica.Room = 5;

			}

			else if (Chica.Room == 8) {

				if (t == 1)
					Chica.Room = 4;

				else
					Chica.Room = 11;

			}

			else if (Chica.Room == 11) {

				if (t == 1)
					Chica.Room = 8;

				else
					Chica.Room = 12;

			}

			else if (Chica.Room == 12) {

				if (Right.Open) {

					Chica.Room = 14;
					Right.Broke = true;
					Right.Lit = false;
					Right.Open = true;

				}

				else
					Chica.Room = 8;

			}

			Chica.Moved = true;
			CheckCameraError(Chica.Room, Chica.Moved);

		}

	}

	if (Chica.Room == 14) {

		if (CameraUp) {

			Chica.Room = 15;
			Chica.WaitTS = GetTime();

		}

	}

	if (Chica.Room == 15 && (!CameraUp || GetTimeSince(Chica.WaitTS) > 15)) {

		CameraUp = false;
		BeginGameOver();
		Chica.Room = 13;

	}

}

void Game::BonnieAI() {

	if (GetTimeSince(Bonnie.MoveTS) > 4.97) {

		Bonnie.MoveTS = GetTime();

		if (MovementOpportunity(Bonnie.AI)) {

			int t = BonnieRNG(generator);

			Bonnie.Moved = true;
			CheckCameraError(Bonnie.Room, Bonnie.Moved);

			if (Bonnie.Room == 1) {

				if (t == 3)
					Bonnie.Room = 4;

				else
					Bonnie.Room = 2;

			}

			else if (Bonnie.Room == 4) {

				if (t == 3)
					Bonnie.Room = 2;

				else
					Bonnie.Room = 7;

			}

			else if (Bonnie.Room == 2) {

				if (t == 3)
					Bonnie.Room = 7;

				else
					Bonnie.Room = 4;

			}

			else if (Bonnie.Room == 7) {

				if (t == 3)
					Bonnie.Room = 6;

				else
					Bonnie.Room = 10;

			}

			else if (Bonnie.Room == 6) {

				if (t == 4)
					Bonnie.Room = 7;

				else
					Bonnie.Room = 12;

			}

			else if (Bonnie.Room == 10) {

				if (t == 3)
					Bonnie.Room = 12;

				else
					Bonnie.Room = 6;

			}

			else if (Bonnie.Room == 12) {

				if (Left.Open) {

					Bonnie.Room = 14;
					Left.Broke = true;
					Left.Lit = false;
					Left.Open = true;

				}

				else
					Bonnie.Room = 4;

			}

			Bonnie.Moved = true;
			CheckCameraError(Bonnie.Room, Bonnie.Moved);

		}

	}

	if (Bonnie.Room == 14) {

		if (CameraUp) {

			Bonnie.Room = 15;
			Bonnie.WaitTS = GetTime();

		}

	}

	if (Bonnie.Room == 15 && (!CameraUp || GetTimeSince(Bonnie.WaitTS) > 15)) {

		CameraUp = false;
		BeginGameOver();
		Bonnie.Room = 13;

	}

}

void Game::SetFoxyLock() {

	Foxy.LockDuration = FoxyRNG(generator);
	Foxy.LockTS = GetTime();

}

void Game::BeginGameOver() {

	if (!GameOver)
		GameOverTS = GetTime();

	GameOver = true;

}

void Game::Draw_Power(int x, int y) {

	if (Power < 0)
		Power = 0;

	DrawSprite(86, x, y + 1);

	if (int(Power) > 9) {

		DrawSprite((int(Power) / 10) + 88, x + 144, y);
		DrawSprite((int(Power) % 10) + 88, x + 155, y);
		DrawSprite(87, x + 166, y);
		DrawSprite(98, x + 185, y);

	}

	else {

		DrawSprite(int(Power) + 88, x + 144, y);
		DrawSprite(87, x + 155, y);
		DrawSprite(98, x + 174, y);
		DrawSprite(98, x + 193, y);

	}

}

void Game::PowerLogic() {

	int tNight = Night;

	if (Night > 5)
		tNight = 5;

	if (GetTimeSince(PenaltyTS) > (8.0 - tNight) && tNight != 1) {

		Power -= 1.3;
		PenaltyTS = GetTime();

	}

	if (GetTimeSince(PowerTS) > (10.00 / Usage)) {
		
		Power -= 1.0;
		PowerTS = GetTime();

	}

}

void Game::Draw_Clock(int x, int y) {

	if (GetTimeSince(GameTS) > 89.0 * (Hour + 1.0))
		Hour++;

	if (Hour < 6)
		DrawSprite(63 + Hour, x, y);

	else
		GameOver = true;
}

void Game::CheckCameraError(int room, bool & moved) {

	if (moved && room == Camera && !AlwaysWorkingCamera&& CameraUp) {

		CameraError = true;
		CameraErrorTS = GetTime();

	}

	moved = false;

}