#include <State.hpp>
#include <StateStack.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& gfonts, Textures::ID& character, Leaderboards& boards, SoundPlayer& sPlayer, ThemePlayer& tPlayer, ColorHolder& cHolder)
	:window(&window)
	, textures(&textures)
	, fonts(&gfonts)
	, currentCharacterID(&character)
	, leaderboards(&boards)
	, soundPlayer(&sPlayer)
	, themePlayer(&tPlayer)
	, colorHolder(&cHolder)
{
}


State::State(StateStack& stack, Context context)
	: stack(&stack)
	, context(context)
{
}

void State::stackPush(GameStates::ID stateID)
{
	stack->pushState(stateID);
}

void State::stackPop()
{
	stack->popState();
}

void State::stackClear()
{
	stack->clearStates();
}
