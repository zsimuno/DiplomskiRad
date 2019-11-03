#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	:window(&window),
	textures(&textures),
	fonts(&fonts)
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
