#include <Platforms.hpp>

#include <memory>

int Platforms::startingPlatform = 0;

Platforms::Platforms(sf::FloatRect& bounds, State::Context gameContext)
	: currentBounds(bounds)
	, context(gameContext)
{
	initialize();
}

bool Platforms::isPlayerOnPlatform(Player& player, float dtAsSeconds)
{
	for (auto p = children.begin(); p != children.end(); p++)
	{
		auto plat = dynamic_cast<Platform*>(p->get());
		if (plat->isPlayerOnPlatform(player, dtAsSeconds))
		{
			return true;
		}
	}
	return false;
}

void Platforms::updateCurrent(sf::Time dt)
{
	// Erase non visible platforms
	for (auto p = children.begin(); p != children.end();)
	{
		auto plat = dynamic_cast<Platform*>(p->get());
		if (plat->getBounds().top > currentBounds.top + currentBounds.height)
		{
			p = children.erase(p);
		}
		else
		{
			break;
		}
	}

	// Add a new platform if there is room for it
	if (dynamic_cast<Platform*>(children.back().get())->getHeight() - platformDistance > currentBounds.top)
	{
		addNewPlatform();
	}

}


void Platforms::initialize()
{
	children.clear();
	attachChild(std::unique_ptr<Platform>(new Platform(Platforms::startingPlatform, currentBounds, context)));
	while (true)
	{
		if (dynamic_cast<Platform*>(children.back().get())->getHeight() - Platform::platformHeight - 100 < currentBounds.top)
		{
			break;
		}
		addNewPlatform();
	}
}

void Platforms::addNewPlatform()
{
	auto p = dynamic_cast<Platform*>(children.back().get());
	attachChild(std::unique_ptr<Platform>(new Platform(p->getPlatformNumber() + 1, currentBounds, context, p->getHeight())));
}
