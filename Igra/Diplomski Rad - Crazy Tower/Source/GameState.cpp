#include <GameState.hpp>


GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	, tower(*context.window, context)
{
	context.themePlayer->play(Themes::ID::InGameTheme);
}

void GameState::draw()
{
	tower.draw();
}

bool GameState::update(sf::Time dt)
{
	tower.update(dt);
	
	if (tower.GameOver())
	{
		context.themePlayer->stop();

		tower.initialize();
		if (context.leaderboards->hasNewHighScore())
		{
			context.soundPlayer->play(Sounds::ID::Applause);
			stackPush(GameStates::ID::EnterName);
		}
		else
		{
			stackPush(GameStates::ID::GameOver);
		}
	}
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed )
	{
		// If "Escape" or "P" pressed then trigger the pause screen
		if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P)
		{
			stackPush(GameStates::ID::Pause);
		}
		
	}

	return true;
}