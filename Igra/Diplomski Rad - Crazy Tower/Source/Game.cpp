#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <MainMenuState.hpp>
#include <PauseState.hpp>
#include <GameState.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: window(sf::VideoMode(1024, 768), "Crazy Tower", sf::Style::Close | sf::Style::Titlebar)
	, tower(window)
	, textures()
	, fonts()
	, stateStack(State::Context(window, textures, fonts))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	fonts.load(Fonts::ID::Main, "Media/Sansation.ttf");
	mStatisticsText.setFont(fonts.get(Fonts::ID::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	registerStates();
	stateStack.pushState(GameStates::ID::Menu);
}
	


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (stateStack.isEmpty())
				window.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Game::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update(sf::Time dt)
{
	stateStack.update(dt);
}

void Game::render()
{
	window.clear();

	stateStack.draw();

	window.setView(window.getDefaultView());
	window.draw(mStatisticsText);

	window.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::registerStates()
{
	stateStack.registerState<MainMenuState>(GameStates::ID::Menu);
	stateStack.registerState<GameState>(GameStates::ID::Game);
	stateStack.registerState<PauseState>(GameStates::ID::Pause);
}
