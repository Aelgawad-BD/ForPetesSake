#pragma once

/*
	This file has all the constants and configurables, no magic numbers in code, no sir!
*/

const char TITLE[] = "Der Jeager Meister";

const int SCREEN_WIDTH = 1400; // 840;
const int SCREEN_HEIGHT = 800; // 480;

const int MARGIN = 40;

const int SPLASH_SCREEN_TIME_DELAY = 1000;

enum ExitCode
{
	FAILED,
	SUCCESS
};

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

enum SpriteSheet_Animation
{
	IDLE = 0,
	WALK = 3,
	RUN = 1,
	JUMP = 4,
	ATTACK = 2,
	HIT,
	DIE,
	count
};

// ToDo: Run the game as a state machine
enum GAME_STATE
{
	IntroScreen,
	MainMenu,
	Paused,
	Stage_one,
	Stage_two
};

/*
	The working directory is where your application thinks it is operating. Typically, your working directory is the directory where
	your executable is at but some programs like Visual Studio change the working directory to where the vcxproj file is located.
	So if your application can't find the image, make sure it is in the right place
*/

/*
	The following is a listing of all the resource files used and referenced in the code
*/

/*
	RULE:
			If a variable name has an underscore file extension at the end, then it is string representing the directory where the resource resides
*/

// Bitmaps
//const std::string img_SplashScreen_bmp = "Resources/Bitmap/splash_screen.bmp";
//const std::string img_Up_bmp = "Resources/Bitmap/up.bmp";
//const std::string img_Down_bmp = "Resources/Bitmap/down.bmp";
//const std::string img_Left_bmp = "Resources/Bitmap/left.bmp";
//const std::string img_Right_bmp = "Resources/Bitmap/right.bmp";
//
//// PNGees
//const std::string img_SplashScreen_png = "Resources/PNG/splash_screen.png";
//
//const std::string img_Up_png = "Resources/PNG/up.png";
//const std::string img_Down_png = "Resources/PNG/down.png";
//const std::string img_Left_png = "Resources/PNG/left.png";
//const std::string img_Right_png = "Resources/PNG/right.png";
//
//
//const std::string img_charcter_png = "Resources/PNG/foo.png";
//
//const std::string spriteSheet_mainCharcter_walkCycle_png = "Resources/PNG/main_walkCycle.png";
//const std::string spriteSheet_UNGCharcter_walkCycle_png = "Resources/PNG/UglyNakedGuy_SpriteSheet.png";

const std::string img_background_png = "Resources/PNG/backscene.png";
const std::string img_level_png = "Resources/PNG/level1.png";
const std::string img_title_png = "Resources/PNG/DerJeagerMeister_title.png";
const std::string img_studio_png = "Resources/PNG/studio.png";

// Jeager Meister -- unsre leiblings held
// maybe they should be member variables, for every object
const std::string spriteSheet_jeagermeister_png = "Resources/JeagerMeister/JeagerMeister.png";

// SPRITE SHEET Standards
//	Ideally, all character sprite sheets should follow the same layout
//	the first row is the Walk animation
//	second is the Running animation