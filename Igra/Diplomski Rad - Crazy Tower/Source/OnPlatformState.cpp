#include <OnPlatformState.hpp>
#include <Player.hpp>
#include <Platform.hpp>




OnPlatformState::OnPlatformState(PlayerContext ctx)
	:PlayerState(ctx)
{
}

void OnPlatformState::update(sf::Time dt)
{
	handleRealTimeEvent();

	Player* pl = context.player;
	Platform* current = pl->getCurrentPlatform();
	if (context.player->getCurrentPlatform() != nullptr)
	{
		sf::FloatRect playerRect(sf::Vector2f(pl->getPosition().x + pl->getBounds().left, pl->getPosition().y + pl->getBounds().top),
			sf::Vector2f(pl->getBounds().width, pl->getBounds().height));

		if (!(playerRect.left + playerRect.width > current->getBounds().left&&
			playerRect.left < current->getBounds().left + current->getBounds().width))
		{
			pl->changeState();
		}
	}
}

void OnPlatformState::handleRealTimeEvent()
{
}

