#include <GameOverState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, gameOverText()
	, elapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::ID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	gameOverText.setString("Game over! \n Press any key to continue!");

	gameOverText.setCharacterSize(70);
	Utility::centerOrigin(gameOverText);
	gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	sf::RenderWindow& window = *getContext().window;
	background = sf::RectangleShape(window.getView().getSize() / 5.0f);
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setSize(window.getView().getSize() * 4.0f / 5.0f);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(background);
	window.draw(gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) 
	{
		requestStateClear();
		requestStackPush(GameStates::ID::Menu);
	}
	return false;
}
