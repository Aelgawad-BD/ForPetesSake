#pragma once

/*
	This file has all the constants and configurables, no magic numbers in code, no sir!
*/

const std::string TITLE = "Title goes here..";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TIME_DELAY = 8000;

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

const std::string img_SplashScreen_dir = "Resources/Bitmap/splash_screen.bmp";
const std::string img_Up_dir = "Resources/Bitmap/up.bmp";
const std::string img_Down_dir = "Resources/Bitmap/down.bmp";
const std::string img_Left_dir = "Resources/Bitmap/left.bmp";
const std::string img_Right_dir = "Resources/Bitmap/right.bmp";