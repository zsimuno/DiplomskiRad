#include <SettingsState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>
#include <Platforms.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>

SettingsState::SettingsState(StateStack& stack, Context context)
	:State(stack, context)
	, settingsMenu(sf::Text("Settings", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y, *context.soundPlayer)
	, selectedCharacter(context.textures->get(*context.currentCharacterID))
{
	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	selectedCharacter.setPosition(sf::Vector2f(context.window->getView().getSize().x / 4, context.window->getView().getSize().y / 2 + 50.f));
	selectedCharacter.setScale(sf::Vector2f(2.5f, 2.5f));
	selectedCharacter.setTextureRect(sf::IntRect(2, 4, 29, 52));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	settingsMenu.setPosition(context.window->getView().getSize().x / 3, 120.f);

	sf::Text volume("Volume:" + std::to_string((int)context.soundPlayer->getVolume()) + "%", font);

	MenuOption volumeOption(volume);

	volumeOption.setLeftRightFunctions(
		[context](MenuOption* option)
		{
			float volume = context.soundPlayer->getVolume();
			if (volume > 0)
			{
				volume -= 10;
			}

			context.soundPlayer->setVolume(volume);
			context.themePlayer->setVolume(volume);

			option->setString("Volume:" + std::to_string((int)volume) + "%");
		}, [context](MenuOption* option)
		{
			float volume = context.soundPlayer->getVolume();
			if (volume < 100)
			{
				volume += 10;
			}

			context.soundPlayer->setVolume(volume);
			context.themePlayer->setVolume(volume);

			option->setString("Volume:" + std::to_string((int)volume) + "%");
		});

	settingsMenu.addSelectableOption(volumeOption);

	std::map<Textures::ID, std::string> charactersMap;

	charactersMap.insert(std::make_pair(Textures::ID::Mike, std::string("Mike")));
	charactersMap.insert(std::make_pair(Textures::ID::Bunny, std::string("Bunny")));
	charactersMap.insert(std::make_pair(Textures::ID::Invisible, std::string("Invisible")));
	charactersMap.insert(std::make_pair(Textures::ID::RedMarine, std::string("Red Man")));
	charactersMap.insert(std::make_pair(Textures::ID::BlueMarine, std::string("BLue Man")));

	sf::Text character("CH: " + charactersMap[*context.currentCharacterID], font);
	MenuOption characterOption(character);
	
	characterOption.setLeftRightFunctions(
			[charactersMap, context, this]( MenuOption* option)
		{
			for (auto ch = charactersMap.begin(); ch != charactersMap.end(); ++ch)
			{
				if (ch->first == *context.currentCharacterID)
				{
					
					if (ch == charactersMap.begin())
					{
						ch = charactersMap.end();
					}

					--ch;

					*context.currentCharacterID = ch->first;
					break;
				}
			}
			option->setString("CH: " + charactersMap.at(*context.currentCharacterID));
			selectedCharacter.setTexture(context.textures->get(*context.currentCharacterID));

		}, [charactersMap, context, this](MenuOption* option)
		{
			for (auto ch = charactersMap.begin(); ch != charactersMap.end(); ++ch)
			{
				if (ch->first == *context.currentCharacterID)
				{
					++ch;
					if (ch == charactersMap.end())
					{
						ch = charactersMap.begin();
					}

					*context.currentCharacterID = ch->first;
					break;
				}
			}
			option->setString("CH: " + charactersMap.at(*context.currentCharacterID));
			selectedCharacter.setTexture(context.textures->get(*context.currentCharacterID));
		});

	settingsMenu.addSelectableOption(characterOption);

	sf::Text floor("Floor: " + std::to_string(Platforms::startingPlatform), font);
	MenuOption floorOption(floor);
	floorOption.setLeftRightFunctions(
			[](MenuOption* option)
		{
			if (Platforms::startingPlatform > 0)
			{
				Platforms::startingPlatform -= 100;
			}
			option->setString("Floor: " + std::to_string(Platforms::startingPlatform));

		}, [](MenuOption* option)
		{
			if (Platforms::startingPlatform < 500)
			{
				Platforms::startingPlatform += 100;
			}
			option->setString("Floor: " + std::to_string(Platforms::startingPlatform));
		});

	settingsMenu.addSelectableOption(floorOption);

	sf::Text back("Go Back", font);
	settingsMenu.addOption(back, [this]()
		{
			stackPop();
		});

}

void SettingsState::draw()
{
	context.window->draw(background);
	context.window->draw(settingsMenu);
	context.window->draw(selectedCharacter);
}

bool SettingsState::update(sf::Time)
{
	return false;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			stackPop();
			return false;
		}
	}

	settingsMenu.handleEvent(event);
	return false;
}

