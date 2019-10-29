#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SceneNode.hpp>
#include <ResourceIdentifiers.hpp>
#include <PlayerData.hpp>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include <map>

class Platforms;
class Platform;
class PlayerAnimation;

class Player :
	public SceneNode
{
public:
	Player(const TextureHolder& textures, Platforms& towerPlatforms);

	void					    handleEvent();
	void					    handleRealtimeInput();
	void					    setVelocity(sf::Vector2f v);
	void					    addVelocity(sf::Vector2f v);
	sf::Vector2f			    getVelocity() const;
	sf::FloatRect			    getBounds() const;
	void					    setOnPlatform(Platform* platform);
	bool					    isStandingOnPlatform() const;
	Platforms&					getPlatforms();
	Platform*					getCurrentPlatform();

private:

	virtual void			    updateCurrent(sf::Time dt) override;
	virtual void			    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite				    sprite;
	sf::Vector2f			    playerVelocity;
	Platforms&					platforms;
	Platform*					currentPlatform;

	PlayerInfo				    data;

	bool					    mirroredSprite;
	bool					    isOnPlatform;
	bool						isInCombo;

	PlayerAnimation*            animation;
};

#endif // PLAYER_HPP