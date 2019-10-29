#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
	:window(&window),
	textures(&textures),
	fonts(&fonts),
	player(&player)
{

}


State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}