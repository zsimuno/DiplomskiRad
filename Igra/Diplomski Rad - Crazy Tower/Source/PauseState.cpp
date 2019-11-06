#include <PauseState.hpp>
#include <Utility.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	:State(stack, context)
	, pauseMenu(sf::Text("Paused", context.fonts->get(Fonts::ID::Main)), context.window->getView().getSize().x, context.window->getView().getSize().y, *context.soundPlayer)
{
	context.soundPlayer->play(Sounds::ID::Pause);
	context.themePlayer->setPaused(true);

	sf::RenderWindow& window = *context.window;
	background = sf::RectangleShape(window.getView().getSize() * 6.0f / 8.0f);
	background.setPosition(window.getView().getSize() / 8.0f);
	background.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font& font = context.fonts->get(Fonts::ID::Main);

	pauseMenu.setPosition(context.window->getView().getSize().x / 3, 120.f);

	sf::Text resume("Resume", font);
	pauseMenu.addOption(resume, [context, this]()
		{
			context.soundPlayer->play(Sounds::ID::Pause);
			context.themePlayer->setPaused(false);
			stackPop();
		});

	sf::Text menu("Main menu", font);
	pauseMenu.addOption(menu, [context, this]()
		{
			context.themePlayer->stop();
			stackClear();
			stackPush(GameStates::ID::Menu);
		});

}


void PauseState::draw()
{
	sf::RenderWindow& window = *context.window;
	window.setView(window.getDefaultView());	

	window.draw(background);
	window.draw(pauseMenu);

}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	pauseMenu.handleEvent(event);
	return false;
}

