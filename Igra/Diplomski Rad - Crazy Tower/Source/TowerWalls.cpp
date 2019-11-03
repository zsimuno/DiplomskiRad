#include <TowerWalls.hpp>
#include <Tower.hpp>

#include <SFML\Graphics\RenderTarget.hpp>
#include <Utility.hpp>

TowerWalls::TowerWalls(float wallWidth, Tower& gameTower, Player& player, State::Context context)
	:tower(gameTower)
	, player(player)
	, leftWall()
	, rightWall()
	, timerText("30", context.fonts->get(Fonts::ID::Main))
	, comboText("  0 \nFloors", context.fonts->get(Fonts::ID::Main))
	, comboTimer()
	, gameSpeedTimer()
	, timerStarted(false)
	, comboNumber(0)
	, comboBarBack(sf::Vector2f((float) comboBarWidth + 10.f, (float) comboBarHeight + 10.f))
	, comboBarFront(sf::Vector2f((float)comboBarWidth, 0.f))
	, barPosition(40, 200)
{
	sf::Texture& texture = context.textures->get(Textures::ID::Walls);
	texture.setRepeated(true);

	sf::IntRect textureRect(0, 0, (int)wallWidth, (int)context.window->getView().getSize().y);
	leftWall.setTexture(texture);
	leftWall.setTextureRect(textureRect);

	textureRect = sf::IntRect((int) context.window->getView().getSize().x - (int) wallWidth, 0, (int)wallWidth, (int)context.window->getView().getSize().y);
	rightWall.setTexture(texture);
	rightWall.setPosition(context.window->getView().getSize().x - wallWidth, 0);
	rightWall.setTextureRect(textureRect);

	Utility::centerOrigin(comboText);

	timerText.setPosition(30, 50);
	comboText.setPosition(60, 200 + comboBarHeight + 45);

	timerText.setCharacterSize(80);
	timerText.setOutlineColor(sf::Color::Black);
	timerText.setOutlineThickness(2);

	comboText.setCharacterSize(40);
	comboText.setOutlineColor(sf::Color::Black);
	comboText.setOutlineThickness(2);

	comboBarBack.setPosition(barPosition - sf::Vector2f(5.f, 5.f));
	comboBarFront.setPosition(barPosition);

	comboBarBack.setFillColor(sf::Color(0x009688FF));
	comboBarFront.setFillColor(sf::Color(0x81D4FAFF));
}
void TowerWalls::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(leftWall, states);
	target.draw(rightWall, states);
	target.draw(timerText, states);
	target.draw(comboText, states);
	target.draw(comboBarBack, states);
	target.draw(comboBarFront, states);
}

void TowerWalls::updateCurrent(sf::Time dt)
{
	int currentCombo = player.getCombo();
	
	if (currentCombo > 0)
	{
		// Restart if player jumped on new platform
		if (comboNumber != currentCombo) 
		{
			comboTimer.restart();
		}
		else if (comboTimer.getElapsedTime().asSeconds() >= 3)
		{
			// Player has 3 seconds to continue the combo
			player.endCombo();
			comboTimer.restart();
		}
		comboNumber = currentCombo;
	}
	else
	{
		comboTimer.restart();
	}

	float timerDiff = (comboTimer.getElapsedTime().asSeconds() * (comboBarHeight / 3));
	comboBarFront.setPosition(barPosition + sf::Vector2f(0.f, timerDiff));
	comboBarFront.setSize( sf::Vector2f(comboBarWidth, comboBarHeight - timerDiff));
	comboText.setString("  " + std::to_string(player.getCombo()) + "\nFloors");

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

void TowerWalls::setGameSpeedTimer(bool state)
{
	timerStarted = state;
}
