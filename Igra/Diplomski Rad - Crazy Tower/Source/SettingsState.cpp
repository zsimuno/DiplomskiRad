#include <SettingsState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Platforms.hpp>
#include <map>



SettingsState::SettingsState(StateStack& stack, Context context)
	:State(stack, context)
	, settingsMenu(sf::Text("Settings", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y, *context.soundPlayer)
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

	sf::Text character("CH: " + charactersMap[*context.currentCharacterID], font);
	MenuOption characterOption(character);
	
	characterOption.setLeftRight(
			[charactersMap, context]( MenuOption* option)
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

		}, [charactersMap, context](MenuOption* option)
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
		});

	settingsMenu.addSelectableOption(characterOption);

	/*std::vector<sf::Vector2u> resolutionVector;

	resolutionVector.push_back(sf::Vector2u(1024, 576));
	resolutionVector.push_back(sf::Vector2u(1280, 720));
	resolutionVector.push_back(sf::Vector2u(1400, 800));
	resolutionVector.push_back(sf::Vector2u(1600, 900));
	resolutionVector.push_back(sf::Vector2u(1920, 1080));


	sf::Text resolutionText(std::to_string(context.window->getSize().x) + "x" + std::to_string(context.window->getSize().y), font);
	MenuOption resolutionOption(resolutionText);

	resolutionOption.setLeftRight(
		[resolutionVector, context](MenuOption* option)
		{
			for (std::size_t i = 0; i < resolutionVector.size(); ++i)
			{
				if (resolutionVector[i].x == context.window->getSize().x)
				{
					if (i == 0)
					{
						i = resolutionVector.size() - 1;
					}
					else
					{
						--i;
					}

					context.window->setSize(resolutionVector[i]);
					break;
				}
			}

			option->setString(std::to_string(context.window->getSize().x) + "x" + std::to_string(context.window->getSize().y));

		}, [resolutionVector, context](MenuOption* option)
		{

			for (std::size_t i = 0; i < resolutionVector.size(); ++i)
			{
				if (resolutionVector[i].x == context.window->getSize().x)
				{
					i = (i + 1) % resolutionVector.size();
					context.window->setSize(resolutionVector[i]);
					break;
				}
			}
			option->setString(std::to_string(context.window->getSize().x) + "x" + std::to_string(context.window->getSize().y));
		});

	settingsMenu.addSelectableOption(resolutionOption);*/


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

