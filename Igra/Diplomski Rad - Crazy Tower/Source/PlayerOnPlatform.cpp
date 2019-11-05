#include <PlayerOnPlatform.hpp>
#include <Player.hpp>
#include <Platform.hpp>




PlayerOnPlatform::PlayerOnPlatform(PlayerContext ctx)
	:PlayerState(ctx)
{
}

void PlayerOnPlatform::update(sf::Time dt)
{
	playerVelocity = context.player->getVelocity();

	playerVelocity.x *= 0.95f * dt.asSeconds();
	float dtAsSeconds = dt.asSeconds();

	this->handleRealtimeInput();

	sf::FloatRect currentPlatformBounds = context.player->getCurrentPlatformBounds();

	if (currentPlatformBounds.width != 0.f)
	{
		sf::FloatRect playerBounds = context.player->getBounds();
		sf::Vector2f playerPosition = context.player->getPosition();

		sf::FloatRect playerRect(sf::Vector2f(playerPosition.x + playerBounds.left, playerPosition.y + playerBounds.top),
								sf::Vector2f(playerBounds.width, playerBounds.height));

		// Is player falling of the platform
		if (!(playerRect.left + playerRect.width > currentPlatformBounds.left&&
			playerRect.left < currentPlatformBounds.left + currentPlatformBounds.width))
		{
			isOnPlatform = false;
			context.player->endCombo();
		}
	}

	context.player->setVelocity(playerVelocity);
}

void PlayerOnPlatform::handleRealtimeInput()
{
	if (isOnPlatform && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		playerVelocity.y -= data.jumpSpeed + 2 * abs(playerVelocity.x);
		isOnPlatform = false;
	}
}

