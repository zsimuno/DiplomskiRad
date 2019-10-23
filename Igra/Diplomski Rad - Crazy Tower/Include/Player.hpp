#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <SceneNode.hpp>
#include <map>
#include <ResourceIdentifiers.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <PlayerData.hpp>


class Player :
	public SceneNode
{

public:
	Player(const TextureHolder& textures, float* scrollSpeed);

	void					handleEvent(const sf::Event& event);
	void					handleRealtimeInput();
	void					setVelocity(sf::Vector2f v);
	void					addVelocity(sf::Vector2f v);
	sf::Vector2f			getVelocity();

private:

	virtual void			updateCurrent(sf::Time dt) override;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite				sprite;
	sf::Vector2f			playerVelocity;
	float*					screenScrollSpeed;

	PlayerInfo				data;

	bool					mirroredSprite;

};

#endif // PLAYER_HPP