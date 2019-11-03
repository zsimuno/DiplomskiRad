#include <GameOverState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, gameOverMenu(sf::Text("Game Over", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y)
{
	sf::RenderWindow& window = *context.window;
	background = sf::RectangleShape(window.getView().getSize() * 6.0f / 8.0f);
	background.setPosition(window.getView().getSize() / 8.0f);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	gameOverMenu.setPosition(0, 0);

	sf::Text restart("Try again", font);
	gameOverMenu.addOption(restart, [this]()
		{
			stackPop();
		});

	sf::Text menu("Main menu", font);
	gameOverMenu.addOption(menu, [this]()
		{
			stackClear();
			stackPush(GameStates::ID::Menu);
		});

}

void GameOverState::draw()
{
	sf::RenderWindow& window = *context.window;
	window.setView(window.getDefaultView());

	window.draw(background);
	window.draw(gameOverMenu);
}

bool GameOverState::update(sf::Time dt)
{
	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	gameOverMenu.handleEvent(event);
	return false;
}
