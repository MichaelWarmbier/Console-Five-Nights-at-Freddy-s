#include "Game.h"
void Game::Draw() {
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

	Draw_LeftDoor(315, 579);
	Draw_RightDoor(433, 579);

	Draw_Usage(10, 610);
	Draw_Power(10, 631);
	Draw_Clock(777, 15);

	if (!ToggleHelp)
		DrawSprite(99, 575, 542);
	else
		DrawSprite(100, 575, 542);
}
void Game::Input() {
	if (!GameOver && GetConsoleWindow() == GetForegroundWindow()) {

		if (KeyIsDown(32, true, false)) {

			CameraUp = !CameraUp;

			if (CameraUp && !Foxy.Lock) {

				Foxy.Lock = true;
				SetFoxyLock();

			}
			else if (!CameraUp)
				Foxy.Lock = false;
		}

		if (KeyIsDown(37, true, false) && CameraUp)
			Camera--;

		if (KeyIsDown(39, true, false) && CameraUp)
			Camera++;

		if (KeyIsDown('A', true, false) && !CameraUp && !Left.Broke) {

			Left.Lit = !Left.Lit;
			if (Right.Lit)
				Right.Lit = false;

		}

		if (KeyIsDown('D', true, false) && !CameraUp && !Right.Broke) {

			Right.Lit = !Right.Lit;
			if (Left.Lit)
				Left.Lit = false;

		}
		if (KeyIsDown('Q', true, false) && !CameraUp && !Left.Broke)
			Left.Open = !Left.Open;

		if (KeyIsDown('E', true, false) && !CameraUp && !Right.Broke)
			Right.Open = !Right.Open;
		
		if (KeyIsDown('H', true, false))
			ToggleHelp = !ToggleHelp;

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

	FoxyAI();
	ChicaAI();

	if (CameraUp && Bonnie.Room == 2 && onethird(generator) == 1)
		Bonnie.Scare = true;
	else
		Bonnie.Scare = false;

	if (Camera < 1)
		Camera = 1;
	if (Camera > 11)
		Camera = 11;

	Usage = !Left.Open + !Right.Open + CameraUp + Left.Lit + Right.Lit;

	if (!FreezePowerDrain)
		PowerLogic();

	if (GameOver && (GetTimeSince(GameOverTS) > 1.3 || Hour == 6)) {

		abort(); // temp
		Freddy.AI = 0;
		Bonnie.AI = 0;
		Chica.AI = 0;
		Foxy.AI = 0;

	}

	if (GetTimeSince(CameraErrorTS) > 4.6 && CameraError)
		CameraError = false;

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

	if (!CameraUp && Bonnie.Room != 13 && Chica.Room != 13 && Freddy.Room != 13 && Foxy.Room != 13)
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

	else if (!CameraUp && GFreddy.Active)
		DrawSprite(56, x, y);

}

void Game::Draw_LeftDoor(int x, int y) {

	if (Left.Open) {

		if (Freddy.Room == 12)
			DrawSprite(80, x, y);

		else if (Bonnie.Room == 12 && Left.Lit && !CameraUp)
			DrawSprite(79, x, y);

		else if (Left.Lit && !CameraUp)
			DrawSprite(81, x, y);

		else if (Left.Broke)
			DrawSprite(77, x, y);

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

		else if (Right.Lit && !CameraUp)
			DrawSprite(81, x, y);

		else if (Right.Broke && !CameraUp)
			DrawSprite(77, x, y);

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

void Game::FoxyAI() {

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
			Power -= 1 + (5 * Foxy.Attempts);
			Foxy.Attempts++;

		}

	}

}

void Game::ChicaAI() {

	if (GetTimeSince(Chica.MoveTS) > 4.98) {

		Chica.MoveTS = GetTime();

		if (MovementOpportunity(Chica.AI)) {

			Chica.Moved = true;
			CheckCameraError();

			if (Chica.Room == 1)
				Chica.Room = 4;

			else if (Chica.Room == 4) {

				int t = onethird(generator);

				if (t == 1)
					Chica.Room = 5;

				else if (t == 2)
					Chica.Room = 9;

				else
					Chica.Room = 8;

			}

			else if (Chica.Room == 5 || Chica.Room == 9)
				Chica.Room = 4;

			else if (Chica.Room == 8) {

				int t = halfandhalf(generator);

				if (t == 1)
					Chica.Room = 4;

				else
					Chica.Room = 11;

			}

			else if (Chica.Room == 11) {

				int t = halfandhalf(generator);

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
					Chica.Room = 4;

			}

			Chica.Moved = true;
			CheckCameraError();

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

void Game::SetFoxyLock() {

	Foxy.LockDuration = FoxyLockDist(generator);
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

	if (Power > 9) {

		DrawSprite((Power / 10) + 88, x + 144, y);
		DrawSprite((Power % 10) + 88, x + 155, y);
		DrawSprite(87, x + 166, y);
		DrawSprite(98, x + 185, y);

	}

	else {

		DrawSprite(Power + 88, x + 144, y);
		DrawSprite(87, x + 155, y);
		DrawSprite(98, x + 174, y);
		DrawSprite(98, x + 193, y);

	}

}

void Game::PowerLogic() {

	int tNight = Night;

	if (Night > 5)
		tNight = 5;

	if (GetTimeSince(PowerTS) > ((10 - (tNight - 1 + ((tNight != 1) * 3))) / (Usage + 1))) {
		
		Power--;
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

void Game::CheckCameraError() {

	if (Freddy.Moved && Freddy.Room == Camera) {

		CameraError = true;
		CameraErrorTS = GetTime();

	}

	if (Bonnie.Moved && Bonnie.Room == Camera) {

		CameraError = true;
		CameraErrorTS = GetTime();

	}

	if (Chica.Moved && Chica.Room == Camera) {

		CameraError = true;
		CameraErrorTS = GetTime();

	}

	Freddy.Moved = false;
	Bonnie.Moved = false;
	Chica.Moved = false;

}