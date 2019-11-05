#include <SettingsState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Platforms.hpp>
#include <map>
#include <iostream>


SettingsState::SettingsState(StateStack& stack, Context context)
	:State(stack, context)
	, settingsMenu(sf::Text("Settings", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y)
{
	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	settingsMenu.setPosition(context.window->getView().getSize().x / 3, 120.f);

	sf::Text volume("Volume", font);

	MenuOption volumeOption(volume);

	volumeOption.setLeftRight(
		[](MenuOption* option)
		{


		}, [](MenuOption* option)
		{

		});

	settingsMenu.addSelectableOption(volumeOption);

	std::map<Textures::ID, std::string> charactersMap;

	charactersMap.insert(std::make_pair(Textures::ID::Mike, std::string("Mike")));
	charactersMap.insert(std::make_pair(Textures::ID::Bunny, std::string("Bunny")));
	charactersMap.insert(std::make_pair(Textures::ID::Invisible, std::string("Invisible")));
	charactersMap.insert(std::make_pair(Textures::ID::RedMarine, std::string("Red Man")));
	charactersMap.insert(std::make_pair(Textures::ID::BlueMarine, std::string("BLue Man")));

	std::vector<Textures::ID> texturesv;

	texturesv.push_back(Textures::ID::Mike);
	texturesv.push_back(Textures::ID::Bunny);
	texturesv.push_back(Textures::ID::Invisible);
	texturesv.push_back(Textures::ID::RedMarine);
	texturesv.push_back(Textures::ID::BlueMarine);

	sf::Text character("CH: " + charactersMap[*context.currentCharacterID], font);
	MenuOption characterOption(character);
	
	characterOption.setLeftRight(
			[charactersMap, context, texturesv]( MenuOption* option)
		{
			for (std::size_t i = 0; i < texturesv.size(); ++i)
			{
				if (texturesv[i] == *context.currentCharacterID)
				{
					if (i == 0)
					{
						i = texturesv.size() - 1;
					}
					else
					{
						--i;
					}
					
					*context.currentCharacterID = texturesv[i];
					break;
				}
			}
			option->setString("CH: " + charactersMap.at(*context.currentCharacterID));

		}, [charactersMap, context, texturesv](MenuOption* option)
		{

			for (std::size_t i = 0; i < texturesv.size(); ++i)
			{
				if (texturesv[i] == *context.currentCharacterID)
				{
					i = (i + 1) % texturesv.size();
					*context.currentCharacterID = texturesv[i];
					break;
				}
			}
			option->setString("CH: " + charactersMap.at(*context.currentCharacterID));
		});

	settingsMenu.addSelectableOption(characterOption);


	sf::Text floor("Floor: " + std::to_string(Platforms::startingPlatform), font);
	MenuOption floorOption(floor);
	floorOption.setLeftRight(
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

