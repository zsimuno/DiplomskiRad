#include <PlayerState.hpp>
#include <Player.hpp>

PlayerState::PlayerContext::PlayerContext(PlayerInfo& data, Player& player)
	: data(&data),
	player(&player)
{
}

PlayerState::PlayerState(PlayerContext ctx)
	:context(ctx)
{
}
