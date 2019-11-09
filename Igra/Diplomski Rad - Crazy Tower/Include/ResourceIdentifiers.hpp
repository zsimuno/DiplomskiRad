#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum class ID
	{
		Tower,
		Mike,
		Bunny,
		Invisible,
		RedMarine,
		BlueMarine,
		Walls,
		Floor1,
		Floor2,
		Floor3,
		Floor4,
		Floor5,
		Floor6,
		KeyboardInstructions,
		SpeedInstructions,
		ComboInstructions,
	};
}

namespace PlayerSprite
{
	enum class ID
	{
		Idle1,
		Walk1,
		Walk2,
		Walk3,
		Walk4,
		Jump1,
		Jump2,
		Jump3,
		Jump,
		Idle2,
		Idle3,
		Shock,
		Rotate,
		Edge2,
		Edge1,
	};
}

namespace Fonts
{
	enum class  ID
	{
		Main,
		Secondary,
	};
}

namespace Sounds
{
	enum class ID
	{
		Good,
		Sweet,
		Great,
		Super,
		Wow,
		Amazing,
		Extreme,
		Fantastic,
		Splendid,
		NoWay,
		HurryUp,
		Hi,
		Jump1,
		Jump2,
		Jump3,
		Falling,
		Ledge,
		Alright,
		MenuMove,
		MenuSelect,
		TryAgain,
		Applause,
		Pause,
	};

}

namespace Themes
{
	enum class ID
	{
		MainMenuTheme,
		InGameTheme,
	};
}

namespace Colors
{
	enum class ID
	{
		Blue,
		Yellow,
		FrontBarColor,
		BackBarColor,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID>			SoundHolder;

#endif // RESOURCEIDENTIFIERS_HPP
