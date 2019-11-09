#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SceneNode.hpp>
#include <ResourceIdentifiers.hpp>
#include <PlayerData.hpp>
#include <PlayerAnimation.hpp>
#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include <map>

class Platforms;
class Platform;
class PlayerAnimation;
class Tower;

class Player : public SceneNode
{
public:
								Player(State::Context& context, Platforms& towerPlatform, Tower& tower);

	void						initialize();

	void					    handleRealtimeInput();

	void					    setVelocity(sf::Vector2f v);
	sf::Vector2f			    getVelocity() const;

	sf::FloatRect			    getBounds() const;

	void					    setOnPlatform(Platform* platform);
	bool					    isStandingOnPlatform() const;
	Platforms&					getPlatforms();
	 sf::FloatRect				getCurrentPlatformBounds() const;
	int							getPlatformNumber();
	int							getHighestPlatform();
	
	int							getCombo();
	int							getHighestCombo();
	bool						isInCombo();
	void						endCombo();

	bool						playerisOnEdge();

	sf::FloatRect				getPrevFrameBounds() const;
private:

	virtual void			    updateCurrent(sf::Time dt) override;
	virtual void			    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite				    sprite;
	sf::Vector2f			    playerVelocity;
	PlayerInfo				    data;
	PlayerAnimation             animation;
	Platforms&					platforms;
	Tower&						tower;
	State::Context&				context;

	sf::FloatRect				currentPlatformBounds;
	sf::FloatRect				prevFrameBounds;
	bool					    isOnPlatform;

	bool						inCombo;
	int							currentCombo;
	int							previousPlatformFloor;
	int							highestPlatform;
	int							maxCombo;

	bool					    mirroredSprite;
	bool						isOnEdge;
};

#endif // PLAYER_HPP