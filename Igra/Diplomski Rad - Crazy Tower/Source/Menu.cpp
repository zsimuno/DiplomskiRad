#include <Menu.hpp>
#include <Utility.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>




Menu::Menu(sf::Text menuTitle, float menuWidth, float menuHeight, SoundPlayer& player)
	: title(menuTitle)
	, titleShadow(menuTitle)
	, width(menuWidth)
	, height(menuHeight)
	, player(player)
	, optionYPosition(menuHeight / 3)
	, selectedOptionIndex(0)
{
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(3);
	title.setCharacterSize(150);
	title.setFillColor(sf::Color(0x01579BFF));
	title.rotate(10);

	titleShadow.setFillColor(sf::Color(0, 0, 0, 150));
	titleShadow.setCharacterSize(150);
	titleShadow.rotate(10);
	titleShadow.setPosition(title.getPosition() + sf::Vector2f(10.f, 10.f));
}

void Menu::addOption(sf::Text optionText, MenuOption::MenuOptionFunction onClick)
{
	addOption(MenuOption(optionText, onClick));
}

void Menu::addSelectableOption(sf::Text optionText, MenuOption::MenuSelectFunction onLeft, MenuOption::MenuSelectFunction onRight)
{
	addSelectableOption(MenuOption(optionText, onLeft, onRight));
}

void Menu::addOption(MenuOption option)
{
	option.setPosition(0.f, optionYPosition);
	options.push_back(option);
	optionYPosition += MenuOption::menuOptionHeight + 15.f;

	if (options.size() == 1)
	{
		options[selectedOptionIndex].select();
	}
}


void Menu::addSelectableOption(MenuOption option)
{
	option.setPosition(0.f, optionYPosition);
	options.push_back(option);
	optionYPosition += MenuOption::menuOptionHeight + 15.f;

	if (options.size() == 1)
	{
		options[selectedOptionIndex].select();
	}
}

void Menu::next()
{
	options[selectedOptionIndex].deselect();

	selectedOptionIndex = (selectedOptionIndex + 1) % options.size();

	options[selectedOptionIndex].select();
}

void Menu::previous()
{
	options[selectedOptionIndex].deselect();

	selectedOptionIndex = (selectedOptionIndex - 1) % options.size();

	options[selectedOptionIndex].select();
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const MenuOption& option : options)
	{
		target.draw(option, states);
	}
	
	target.draw(titleShadow, states);
	target.draw(title, states);
}

void Menu::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		// Check if the mouse is hovering over an option
	case sf::Event::MouseMoved:
		for (size_t i = 0; i < options.size(); ++i)
		{
			if (options[i].contains(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y), this->getPosition()))
			{
				options[selectedOptionIndex].deselect();
				selectedOptionIndex = i;
				options[selectedOptionIndex].select();
				return;
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		// Mouse can only be pressed on the selected option
		if (options[selectedOptionIndex].contains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y), this->getPosition()))
		{
			player.play(Sounds::ID::MenuSelect);
			options[selectedOptionIndex].click();

			// Press left or right arrow if possible
			if (options[selectedOptionIndex].leftContains(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y), this->getPosition()))
			{
				options[selectedOptionIndex].pressLeft();
			}
			else
			{
				options[selectedOptionIndex].pressRight();
			}
		}
		break;

	case sf::Event::KeyPressed:

		switch (event.key.code)
		{
		case sf::Keyboard::Return:
		case sf::Keyboard::Space:
			options[selectedOptionIndex].click();
			player.play(Sounds::ID::MenuSelect);
			break;

		case sf::Keyboard::Up:
			previous();
			player.play(Sounds::ID::MenuMove);
			break;

		case sf::Keyboard::Down:
			next();
			player.play(Sounds::ID::MenuMove);
			break;

		case sf::Keyboard::Left:
			options[selectedOptionIndex].pressLeft();
			player.play(Sounds::ID::MenuSelect);
			break;

		case sf::Keyboard::Right:
			options[selectedOptionIndex].pressRight();
			player.play(Sounds::ID::MenuSelect);
			break;
		}

		break;
	}


}

