#include <GameState.hpp>

GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	, tower(*context.window)
{
}

void GameState::draw()
{
	tower.draw();
}

bool GameState::update(sf::Time dt)
{
	tower.update(dt);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed )
	{
		if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)
		{
			requestStackPush(GameStates::ID::Pause);
		}
		
	}

	return true;
}