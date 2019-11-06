#include <InstructionsState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

InstructionsState::InstructionsState(StateStack& stack, Context context)
	:State(stack, context)
	, keyboardInstructions(context.textures->get(Textures::ID::KeyboardInstructions))
	, comboInstructions(context.textures->get(Textures::ID::ComboInstructions))
	, speedInstructions(context.textures->get(Textures::ID::SpeedInstructions))
{
	// Set background texture
	sf::Texture& texture = context.textures->get(Textures::ID::Tower);
	sf::IntRect textureRect(0, 0, (int)context.window->getView().getSize().x, (int)context.window->getView().getSize().y);
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(textureRect);

	keyboardInstructions.setPosition(50.f, 50.f);
	comboInstructions.setPosition(context.window->getView().getSize().x / 2, context.window->getView().getSize().y / 3);
	speedInstructions.setPosition(50.f, 400.f);

	float scale = 0.5f;
	comboInstructions.setScale(scale, scale);
	speedInstructions.setScale(scale, scale);
}


void InstructionsState::draw()
{
	context.window->draw(background);
	context.window->draw(keyboardInstructions);
	context.window->draw(comboInstructions);
	context.window->draw(speedInstructions);
}

bool InstructionsState::update(sf::Time)
{
	return false;
}

bool InstructionsState::handleEvent(const sf::Event& event)
{
	// On any key press return to main menu
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
	{
		stackPop();
		context.soundPlayer->play(Sounds::ID::MenuSelect);
	}

	return false;
}


