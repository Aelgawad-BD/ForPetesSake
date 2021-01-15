#pragma once
#include "Entity.h"

class SplashScreen :
	public Entity
{
private:

	int displayDuration;
	int fadeSpeed;


public:

	Uint8 currentAlpha = 0;

	SplashScreen();
	SplashScreen(int display_duration, int fade_speed);

	void SetFadeSpeed(int fade_speed);
	void SetDisplayDuration(int time_ms);

	void Show();

	void FadeIn();
	void FadeOut();
};