#include  "FNAF.h"
#include "Game.h"

/* Main Program */

int main() {
	SetConsoleSize();
	ShowConsoleCursor(false);
	FNAF* Program = new FNAF;

	Program->BeginGame();
	SetConsoleTitleA("Five Nights at Freddy's");
	while (Program->GameStatus()) {
		Program->Gameplay.Draw();
		Program->Gameplay.Input();
		Program->Gameplay.Logic();
	}

	return EXIT_SUCCESS;
}

/* Program method definitions */
void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool KeyIsDown(char key, bool pressed, bool held) {
	int keyState = GetAsyncKeyState(static_cast<int>(key));
	return (pressed && (keyState & 1)) || (held && (keyState & 0xA000));
}

void SetConsoleSize() {
	HWND console = GetConsoleWindow();
	HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTOPRIMARY);

	MONITORINFOEX miex;
	miex.cbSize = sizeof(miex);
	GetMonitorInfo(monitor, &miex);
	int cxLogical = (miex.rcMonitor.right - miex.rcMonitor.left);
	int cyLogical = (miex.rcMonitor.bottom - miex.rcMonitor.top);

	// Physical Width/Height
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmDriverExtra = 0;
	EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
	int cxPhysical = dm.dmPelsWidth;
	int cyPhysical = dm.dmPelsHeight;

	double horzScale = ((double)cxPhysical / (double)cxLogical);
	double vertScale = ((double)cyPhysical / (double)cyLogical);

	SetWindowPos(console, HWND_TOP, 0, 0, double(857) / horzScale + 4, double(705) / vertScale, SWP_NOMOVE); // Resize without moving where the console window was placed

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

double GetTime() {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9;
}

double GetTimeSince(double startTime) {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9 - startTime;
}

double Wait(double waitTime) {
	double startTime = GetTime();

	while (waitTime > GetTimeSince(startTime)) {}

	return GetTimeSince(startTime + waitTime);
}

void DrawSprite(int ArrPos, int x, int y) {
	SelectObject(hdc, bmap);
	BitBlt(console, x, y, SpriteInfo[ArrPos - 1][2], SpriteInfo[ArrPos - 1][3], hdc, SpriteInfo[ArrPos - 1][0], SpriteInfo[ArrPos - 1][1], SRCCOPY);
	DeleteObject(bmap);
}
