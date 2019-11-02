#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SceneNode.hpp>
#include <ResourceIdentifiers.hpp>
#include <PlayerData.hpp>
#include <PlayerAnimation.hpp>

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
	Player(const TextureHolder& textures, Platforms& towerPlatform, sf::FloatRect& bounds);

	void						initialize();

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
	
	void						endCombo();

	sf::Sprite				    sprite;
	sf::Vector2f			    playerVelocity;
	Platforms&					platforms;
	Platform*					currentPlatform;
	sf::FloatRect&				currentBounds;

	PlayerInfo				    data;
	PlayerAnimation             animation;

	bool					    mirroredSprite;
	bool					    isOnPlatform;

	bool						isInCombo;
	int							currentCombo;
	int							maxCombo;
};

#endif // PLAYER_HPP