#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <MainMenuState.hpp>
#include <PauseState.hpp>
#include <GameState.hpp>
#include <GameOverState.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: window(sf::VideoMode(1280, 800), "Crazy Tower", sf::Style::Close | sf::Style::Titlebar)
	, textures()
	, fonts()
	, stateStack(State::Context(window, textures, fonts))
{
	fonts.load(Fonts::ID::Main, "Media/Sansation.ttf");

	textures.load(Textures::ID::Character, "Media/Textures/character.png");
	textures.load(Textures::ID::Tower, "Media/Textures/background.png");

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

	window.display();
}


void Game::registerStates()
{
	stateStack.registerState<MainMenuState>(GameStates::ID::Menu);
	stateStack.registerState<GameState>(GameStates::ID::Game);
	stateStack.registerState<PauseState>(GameStates::ID::Pause);
	stateStack.registerState<GameOverState>(GameStates::ID::GameOver);
}
