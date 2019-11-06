#include <GameOverState.hpp>
#include <Utility.hpp>
#include <Player.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, gameOverMenu(sf::Text("Game Over", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y, *context.soundPlayer)
	, leaderboardsText(context.leaderboards->getBoardsText(), context.fonts->get(Fonts::ID::Main))
{
	context.themePlayer->stop();

	sf::RenderWindow& window = *context.window;
	background = sf::RectangleShape(window.getView().getSize());
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	gameOverMenu.setPosition(context.window->getView().getSize().x / 5, 50.f);

	leaderboardsText.setFillColor(sf::Color::White);
	leaderboardsText.setOutlineColor(sf::Color::Black);
	leaderboardsText.setOutlineThickness(2);
	leaderboardsText.setPosition(context.window->getView().getSize().x * 2 / 3, context.window->getView().getSize().y * 2 / 5);

	sf::Text restart("Try again", font);
	gameOverMenu.addOption(restart, [context, this]()
		{
			context.themePlayer->play(Themes::ID::InGameTheme);
			context.soundPlayer->play(Sounds::ID::Hi);
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
	window.draw(leaderboardsText);
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
