#include <GameState.hpp>

GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	, mWorld(*context.window)
	, mPlayer(*context.player)
{
}

void GameState::draw()
{
}

bool GameState::update(sf::Time dt)
{
	return false;
}

bool GameState::handleEvent(const sf::Event& event)
{
	return false;
}

