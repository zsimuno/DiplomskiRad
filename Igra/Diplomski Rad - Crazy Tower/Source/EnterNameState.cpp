#include <EnterNameState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


EnterNameState::EnterNameState(StateStack& stack, Context context)
	: State(stack, context)
	, title("New Record!", context.fonts->get(Fonts::ID::Main))
	, nameEnterLabel("Press ENTER when done!", context.fonts->get(Fonts::ID::Main))
	, nameInputString("***")
	, nameInput(nameInputString, context.fonts->get(Fonts::ID::Main))
	, currentCharacter(0)
{
	context.themePlayer->stop();

	sf::RenderWindow& window = *context.window;
	background = sf::RectangleShape(window.getView().getSize());
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	Utility::centerOrigin(title);
	Utility::centerOrigin(nameEnterLabel);
	Utility::centerOrigin(nameInput);

	title.setPosition(context.window->getView().getSize().x / 5, 50.f);
	title.setFillColor(sf::Color::White);
	title.setOutlineThickness(3);
	title.setCharacterSize(150);
	title.setOutlineColor(context.colorHolder->get(Colors::ID::Blue));

	nameEnterLabel.setCharacterSize(90);
	nameInput.setCharacterSize(120);

	nameEnterLabel.setFillColor(sf::Color::White);
	nameEnterLabel.setOutlineThickness(3);
	nameEnterLabel.setOutlineColor(context.colorHolder->get(Colors::ID::Blue));

	nameInput.setOutlineColor(sf::Color::White);
	nameInput.setOutlineThickness(3);
	nameInput.setFillColor(context.colorHolder->get(Colors::ID::Blue));

	nameEnterLabel.setPosition(context.window->getView().getSize().x / 4, context.window->getView().getSize().y / 2);
	nameInput.setPosition(context.window->getView().getSize().x / 2, context.window->getView().getSize().y / 2 + 140.f);

}


void EnterNameState::draw()
{
	sf::RenderWindow& window = *context.window;
	window.setView(window.getDefaultView());

	window.draw(background);
	window.draw(title);
	window.draw(nameEnterLabel);
	window.draw(nameInput);
}

bool EnterNameState::update(sf::Time dt)
{
	// Blink text every second
	if (blinkTimer.getElapsedTime().asSeconds() > 1.f)
	{
		blinkTimer.restart();
		std::string str = nameInput.getString();
		if (str[currentCharacter] == '_')
		{
			str[currentCharacter] = nameInputString[currentCharacter];
		}
		else
		{
			str[currentCharacter] = '_';
		}

		nameInput.setString(str);
	}
	return false;
}

bool EnterNameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Return:
		case sf::Keyboard::Escape:
			context.leaderboards->addNewScore(nameInputString);
			stackPop();
			stackPush(GameStates::ID::GameOver);
			break;

		case sf::Keyboard::Left:
			currentCharacter--;
			if (currentCharacter < 0)
			{
				currentCharacter = 2;
			}
			nameInput.setString(nameInputString);
			break;
		case sf::Keyboard::Right:
			currentCharacter = (currentCharacter + 1) % 3;
			nameInput.setString(nameInputString);
			break;
		default:
			break;
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			nameInputString[currentCharacter] = event.text.unicode;
			nameInput.setString(std::string(nameInputString));

			currentCharacter = (currentCharacter + 1) % 3;
		}
	}

	return false;
}
