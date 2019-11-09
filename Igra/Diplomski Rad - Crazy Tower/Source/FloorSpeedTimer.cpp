#include <FloorSpeedTimer.hpp>
#include <Tower.hpp>

FloorSpeedTimer::FloorSpeedTimer(State::Context gameContext, Tower& gameTower, Player& player)
	:tower(gameTower)
	, player(player)
	, timerText("30", gameContext.fonts->get(Fonts::ID::Main))
	, hurryUpText("Hurry Up!", gameContext.fonts->get(Fonts::ID::Secondary))
	, gameSpeedTimer()
	, timerStarted(false)
	, context(gameContext)
	, hurryUpPosition(150.f, 0.f)
{
	timerText.setCharacterSize(80);
	timerText.setOutlineColor(sf::Color::Black);
	timerText.setOutlineThickness(2);

	hurryUpText.setCharacterSize(60);
	hurryUpText.setFillColor(sf::Color(context.colorHolder->get(Colors::ID::Blue)));
	hurryUpText.setOutlineColor(sf::Color::White);
	hurryUpText.setOutlineThickness(2);
	hurryUpText.setPosition(hurryUpPosition);
}

void FloorSpeedTimer::updateCurrent(sf::Time dt)
{
	// Timer is started when the floors start moving
	if (!timerStarted)
	{
		gameSpeedTimer.restart();
		timerText.setString("30");
		return;
	}

	// Increase game speed every 30 seconds
	float timerTime = gameSpeedTimer.getElapsedTime().asSeconds();
	if (timerTime >= 30)
	{
		gameSpeedTimer.restart();
		tower.incrementScrollSpeed();
		context.soundPlayer->play(Sounds::ID::HurryUp);
	}

	// If "Hurry Up" is showing shake the text
	if (timerTime >= 0.f && timerTime <= 1.f && tower.ScrollSpeed() < Tower::ScrollSpeedIncrement)
	{
		float dirOne = rand() % 6 - 3;
		float dirTwo = rand() % 6 - 3;
		hurryUpText.setPosition(hurryUpPosition + sf::Vector2f(dirOne, dirTwo));
	}

	timerText.setString(std::to_string((int)(30 - timerTime)));
}

void FloorSpeedTimer::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(timerText, states);

	// Draw "Hurry Up" only for one second
	float timerTime = gameSpeedTimer.getElapsedTime().asSeconds();
	if (timerTime >= 0.f && timerTime <= 1.f && tower.ScrollSpeed() < Tower::ScrollSpeedIncrement)
	{
		target.draw(hurryUpText, states);
	}
	
}

void FloorSpeedTimer::setGameSpeedTimer(bool state)
{
	timerStarted = state;
}
