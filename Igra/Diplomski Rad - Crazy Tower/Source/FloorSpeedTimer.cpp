#include <FloorSpeedTimer.hpp>
#include <Tower.hpp>

FloorSpeedTimer::FloorSpeedTimer(State::Context gameContext, Tower& gameTower, Player& player)
	:tower(gameTower)
	, player(player)
	, timerText("30", gameContext.fonts->get(Fonts::ID::Main))
	, gameSpeedTimer()
	, timerStarted(false)
{
	timerText.setCharacterSize(80);
	timerText.setOutlineColor(sf::Color::Black);
	timerText.setOutlineThickness(2);
}

void FloorSpeedTimer::updateCurrent(sf::Time dt)
{
	// Timer is started when the floors start moving
	if (!timerStarted)
	{
		gameSpeedTimer.restart();
		return;
	}

	// Increase game speed every 30 seconds
	float timerTime = gameSpeedTimer.getElapsedTime().asSeconds();
	if (timerTime >= 30)
	{
		gameSpeedTimer.restart();
		tower.incrementScrollSpeed();
	}

	timerText.setString(std::to_string((int)(30 - timerTime)));
}

void FloorSpeedTimer::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(timerText, states);
}

void FloorSpeedTimer::initialize()
{
}
void FloorSpeedTimer::setGameSpeedTimer(bool state)
{
	timerStarted = state;
}
