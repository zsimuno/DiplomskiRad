#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>


struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;


public:
	SceneNode();
	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;


private:
	virtual void			updateCurrent(sf::Time dt);
	void					updateChildren(sf::Time dt);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Ptr>		mChildren;
	SceneNode* mParent;
};


#endif // SCENENODE_HPP
