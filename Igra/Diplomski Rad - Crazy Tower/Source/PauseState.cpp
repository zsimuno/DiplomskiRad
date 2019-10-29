#include <PauseState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	:State(stack, context)
	, pausedText()
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	pausedText.setFont(font);
	pausedText.setString("Game Paused \n Press 'escape' to return to game and 'm' to go ti main menu");
	pausedText.setCharacterSize(70);
	Utility::centerOrigin(pausedText);
	pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	sf::RenderWindow& window = *getContext().window;
	background = sf::RectangleShape(window.getView().getSize() / 5.0f);
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setSize(window.getView().getSize() * 4.0f / 5.0f);
}


void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());	

	window.draw(background);
	window.draw(pausedText);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) 
		{
			requestStackPop();
		}
		else if (event.key.code == sf::Keyboard::M)
		{
			requestStateClear();
			requestStackPush(GameStates::ID::Menu);
		}
	}
	return false;
}

