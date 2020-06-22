#pragma once

/*
	This file has all the constants and configurables, no magic numbers in code, no sir!
*/

const std::string TITLE = "From Const Variable with Love";
// const char* oink = "From Const Variable with Love";
const int SCREEN_WIDTH = 1250; // 840;
const int SCREEN_HEIGHT = 600; // 480;
const int TIME_DELAY = 2000;

enum ExitCode
{
	FAILED,
	SUCCESS
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

/*
	The working directory is where your application thinks it is operating. Typically, your working directory is the directory where
	your executable is at but some programs like Visual Studio change the working directory to where the vcxproj file is located.
	So if your application can't find the image, make sure it is in the right place
*/

// Bitmaps
const std::string img_SplashScreen_bmp = "Resources/Bitmap/splash_screen.bmp";
const std::string img_Up_bmp = "Resources/Bitmap/up.bmp";
const std::string img_Down_bmp = "Resources/Bitmap/down.bmp";
const std::string img_Left_bmp = "Resources/Bitmap/left.bmp";
const std::string img_Right_bmp = "Resources/Bitmap/right.bmp";

// PNGees
const std::string img_SplashScreen_png = "Resources/PNG/splash_screen.png";
const std::string img_Up_png = "Resources/PNG/up.png";
const std::string img_Down_png = "Resources/PNG/down.png";
const std::string img_Left_png = "Resources/PNG/left.png";
const std::string img_Right_png = "Resources/PNG/right.png";

const std::string img_background_png = "Resources/PNG/backscene.png";
const std::string img_charcter_png = "Resources/PNG/foo.png";

const std::string spriteSheet_mainCharcter_walkCycle_png = "Resources/PNG/main_walkCycle.png";