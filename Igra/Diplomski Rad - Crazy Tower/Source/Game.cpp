#include <Game.hpp>
#include <MainMenuState.hpp>
#include <PauseState.hpp>
#include <GameState.hpp>
#include <GameOverState.hpp>
#include <InstructionsState.hpp>
#include <SettingsState.hpp>
#include <EnterNameState.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: window(sf::VideoMode(1400, 800), "Crazy Tower", sf::Style::Close | sf::Style::Titlebar)
	, textures()
	, fonts()
	, currentCharacter(Textures::ID::Mike)
	, leaderboards()
	, themePlayer()
	, soundPlayer()
	, colorHolder()
	, stateStack(State::Context(window, textures, fonts, currentCharacter, leaderboards, soundPlayer, themePlayer, colorHolder))
{
	loadResources();
	insertColors();
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

			// Check if stack is empty on every update
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
	stateStack.registerState<InstructionsState>(GameStates::ID::Instructions); 
	stateStack.registerState<SettingsState>(GameStates::ID::Settings);
	stateStack.registerState<EnterNameState>(GameStates::ID::EnterName);
}

void Game::loadResources()
{
	fonts.load(Fonts::ID::Main, "Media/Thug.ttf");
	fonts.load(Fonts::ID::Secondary, "Media/Orange_Juice.ttf");

	textures.load(Textures::ID::Mike, "Media/Textures/mike.png");
	textures.load(Textures::ID::Bunny, "Media/Textures/bunny.png");
	textures.load(Textures::ID::Invisible, "Media/Textures/invisible.png");
	textures.load(Textures::ID::RedMarine, "Media/Textures/red_marine.png");
	textures.load(Textures::ID::BlueMarine, "Media/Textures/blue_marine.png");
	textures.load(Textures::ID::Tower, "Media/Textures/background.png");
	textures.load(Textures::ID::Walls, "Media/Textures/walls.png");
	textures.load(Textures::ID::Floor1, "Media/Textures/floor1.png");
	textures.load(Textures::ID::Floor2, "Media/Textures/floor2.png");
	textures.load(Textures::ID::Floor3, "Media/Textures/floor3.png");
	textures.load(Textures::ID::Floor4, "Media/Textures/floor4.png");
	textures.load(Textures::ID::Floor5, "Media/Textures/floor5.png");
	textures.load(Textures::ID::Floor6, "Media/Textures/floor6.png");
	textures.load(Textures::ID::KeyboardInstructions, "Media/Textures/keyboard_instructions.png");
	textures.load(Textures::ID::ComboInstructions, "Media/Textures/combo_instructions.png");
	textures.load(Textures::ID::SpeedInstructions, "Media/Textures/speed_instructions.png");

}

void Game::insertColors()
{
	colorHolder.set(Colors::ID::Blue, sf::Color(0x01579BFF));
	colorHolder.set(Colors::ID::Yellow, sf::Color(0xFFC107FF));
	colorHolder.set(Colors::ID::FrontBarColor, sf::Color(0x81D4FAFF));
	colorHolder.set(Colors::ID::BackBarColor, sf::Color(0x009688FF));
}
