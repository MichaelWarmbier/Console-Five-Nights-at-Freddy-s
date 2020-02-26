#include <iostream>
#include <windows.h>
#include <ctime>
#include <tchar.h>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

/* Spritesheet bitmap transfer related */
static HDC console = GetDC(GetConsoleWindow());

static HDC hdc = CreateCompatibleDC(NULL);

static HBITMAP bmap = (HBITMAP)LoadImage(NULL, _T("FNAF_Sprites.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

/* Animatronic class */
class Animatronic {
public:

	int AI, Room, Stage, Attempts;

	double MoveTS, WaitTS, RunTS, LockTS, LockDuration;

	bool Running, Waiting, Lock, Active, Scare, Moved;

};

/* Door class */
class Door {
public:

	bool Lit, Open, Broke;

};

/* Sprite Data */
const int SpriteInfo[102][4] {
	/*	X	  Y	     W	   H      */

		/* Variants of Show Stage */// Room 1
		0,    0,   236,    68, // Hidden					1
		0,   68,   236,    68, // Empty						2
		0,  136,   236,    68, // ERROR						3
		0,  204,   236,    68, // Freddy					4
		0,  272,   236,    68, // Bonnie, Freddy			5
		0,  340,   236,    68, // Chica, Freddy				6
		0,  408,   236,    68, // Bonnie, Chica, Freddy		7
		/* Variants of Backstage */// Room 2			
	  236,    0,   112,   142, // Hidden					8
	  236,  142,   112,   142, // Empty						9
	  236,  284,   112,   142, // ERROR						10
	  236,  426,   112,   142, // Bonnie					11
	  236,  568,   112,   142, // Bonnie ALT				12
		/* Variants of Bathrooms */// Room 5
	  348,    0,   182,   238, // Hidden					13
	  348,  238,   182,   238, // Empty						14
	  348,  476,   182,   238, // ERROR						15
	  348,  714,   182,   238, // Freddy					16
	  348,  952,   182,   238, // Chica						17
		/* Variants of Pirate Cove */// Room 3
	  530,    0,    86,    98, // Hidden					18
	  530,   98,    86,    98, // ERROR						19
	  530,  196,    86,    98, // Foxy 3					20
	  530,  294,    86,    98, // Foxy 2					21
	  530,  392,    86,    98, // Foxy 1					22
	  530,  490,    86,    98, // Warning					23
		/* Variants of Party Room */// Room 4
	  612,    0,   530,   282, // Hidden					24
	  612,  282,   530,   282, // Empty						25
	  612,  564,   530,   282, // ERROR						26
	  612,  846,   530,   282, // Freddy					27
	  612, 1128,   530,   282, // Chica						28
	  612, 1410,   530,   282, // Bonnie					29
	  612, 1692,   530,   282, // Bonnie, Chica				30
		/* Variants of West Hallway */// Room 7
	1142,    0,    94,   158, // Hidden						31
	1142,  158,    94,   158, // Empty						32
	1142,  316,    94,   158, // ERROR						33
	1142,  474,    94,   158, // Bonnie						34
	1142,  632,    94,   158, // Foxy						35
		/* Variants of East Hallway */// Room 8
	1142,    0,    94,   158, // Hidden						36
	1142,  158,    94,   158, // Empty						37
	1142,  316,    94,   158, // ERROR						38
	1236,  474,    94,   158, // Chica						39
	1236,  632,    94,   158, // Freddy						40
	1236,  790,    94,   158, // G. Freddy					41 -- Unused
		/* Variants of Kitchen */// Room 9
	1330,    0,   182,   162, // Hidden						42
	1330,  324,   182,   162, // Chica						43
	1330,  486,   182,   162, // Freddy 					44
	1330,  162,   182,   162, // Quiet						45
		/* Variants of West & East Corner */// Room 10 & 11		
	1512,    0,    94,   137, // Hidden						46
	1512,  137,    94,   137, // Empty						47
	1512,  274,    94,   137, // ERROR						48
	1512,  411,    94,   137, // Chica						49
	1512,  548,    94,   137, // Freddy						50
	1512,  685,    94,   137, // Bonnie						51
		/* Variants of Closet */// Room 6
	1724,    0,   112,   142, // Hidden						52
	1724,  142,   112,   142, // Empty						53
	1724,  284,   112,   142, // Error						54
	1724,  426,   112,   142, // Bonnie						55
		/* Variants of Office */// Room 13
	1606,    0,    92,   122, // Hidden						56
	1606,  122,    92,   122, // Normal						57
	1606,  244,    92,   122, // Bonnie Loss				58
	1606,  366,    92,   122, // Chica Loss					59
	1606,  488,    92,   122, // Freddy Loss				60
	1606,  610,    92,   122, // Foxy Loss					61
	1606,  732,    92,   122, // G. Freddy					62
		/* Other */
	   5,  613,    57,   14, // 12 AM						63
	   5,  635,    57,   14, //  1 AM						64
	   5,  657,    57,   14, //  2 AM						65
	   5,  679,    57,   14, //  3 AM						66
	   5,  701,    57,   14, //  4 AM						67
	   5,  723,    57,   14, //  5 AM						68

	  84,  637,   112,   18, // Usage:						69
	  84,  660,   112,   18, // Usage: |					70
	  84,  683,   112,   18, // Usage: ||					71
	  84,  706,   112,   18, // Usage: |||					72
	  84,  729,   112,   18, // Usage: ||||					73
	  84,  752,   112,   18, // Usage: |||||				74

	1698,    0,   26,   30, // Open Door					75
	1698,   30,   26,   30, // Closed Door					76
	1698,   60,   26,   30, // ERROR						77
	1698,   90,   26,   30, // Chica Warning				78
	1698,  120,   26,   30, // Bonnie Warning				79
	1698,  150,   26,   30, // Freddy Warning				80
	1698,  180,   26,   30, // Open Door LIGHT				81
	1698,  210,   26,   30, // Closed Door Left LIGHT		82
	1698,  240,   26,   30, // Closed Door Right LIGHT		83
	1698,  270,   26,   30, // Closed Door Right LIGHT SCARE84
	1698,  300,   26,   30, // Closed Door Left LIGHT SCARE 85

	  70,  548,  144,   13, // Power Remaning				86

	 207,  640,   19,   15, // %							87
	 207,  663,   11,   15, // 0							88
	 207,  686,   11,   15, // 1							89
	 207,  709,   11,   15, // 2							90
	 207,  732,   11,   15, // 3							91
	 207,  755,   11,   15, // 4							92
	 207,  778,   11,   15, // 5							93
	 207,  801,   11,   15, // 6							94
	 207,  824,   11,   15, // 7							95
	 207,  847,   11,   15, // 8							96
	 207,  870,   11,   15, // 9							97
	 207,  900,   19,   15, // Num EMPTY					98


	  24,  963,  210,  110, // Instructions					99		  
	  24, 1073,  210,  110, // Instructions EMPTY			100		  
	   5,  816,   53,   15, // IT'S ME						101
    1512,  795,   94,  137, // G. Freddy East Hall			102

};

void ShowConsoleCursor(bool ShowFlag); // Hides console cursor

bool KeyIsDown(char key, bool pressed, bool held); // Returns true if specified key is pressed or held

void SetConsoleSize(); // Resizes the console window

double GetTime(); // Returns unix time in seconds

double GetTimeSince(double startTime); // Returns time since given time in seconds

double Wait(double waitTime); // Pauses program and returns duration of pause

void DrawSprite(int ArrPos, int x, int y); // Draws sprite from SpriteInfo at x and y in pixels