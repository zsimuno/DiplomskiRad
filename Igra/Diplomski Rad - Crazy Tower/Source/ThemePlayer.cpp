#include <ThemePlayer.hpp>

ThemePlayer::ThemePlayer()
	: currentTheme()
	, volume(100.f)
{
	themeFiles[Themes::ID::MainMenuTheme] = "Media/Sound/Themes/comedy_theme.wav";
	themeFiles[Themes::ID::InGameTheme] = "Media/Sound/Themes/yummie.wav";
}

void ThemePlayer::play(Themes::ID theme)
{
	currentTheme.openFromFile(themeFiles[theme]);

	currentTheme.setVolume(volume);
	currentTheme.setLoop(true);
	currentTheme.play();
}

void ThemePlayer::stop()
{
	currentTheme.stop();
}

void ThemePlayer::setVolume(float vol)
{
	volume = vol;
	currentTheme.setVolume(vol);
}

float ThemePlayer::getVolume()
{
	return volume;
}


void ThemePlayer::setPaused(bool paused)
{
	if (paused)
		currentTheme.pause();
	else
		currentTheme.play();
}
