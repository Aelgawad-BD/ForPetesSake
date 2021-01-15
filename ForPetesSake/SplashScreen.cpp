#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	// Splash screens are always centered
	int centerX = (SCREEN_WIDTH / 2) - (this->GetScaledWidth() / 2);
	int centerY = (SCREEN_HEIGHT / 2) - (this->GetScaledHeight() / 2);
	SetPosition(centerX, centerY);


	texture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

SplashScreen::SplashScreen(int duration_display, int fade_speed)
{
	SplashScreen();
	SetDisplayDuration(duration_display);
	SetFadeSpeed(fade_speed);
}


void SplashScreen::SetFadeSpeed(int time_ms)
{
	this->fadeSpeed = time_ms;
}

void SplashScreen::SetDisplayDuration(int time_ms)
{
	this->displayDuration = time_ms;
}

void SplashScreen::Show()
{
	FadeIn();
	SDL_Delay(this->displayDuration);
	FadeOut();
}


void SplashScreen::FadeIn()
{
	while (currentAlpha <= 255)
	{
		SDL_Delay(8);
		currentAlpha += 20;
		this->Draw(NULL);
	}
}

void SplashScreen::FadeOut()
{
	while (currentAlpha >= 0)
	{
		SDL_Delay(8);
		currentAlpha += 20;
		this->Draw(NULL);
	}
}