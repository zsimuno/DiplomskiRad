#include <SceneNode.hpp>

#include <cassert>

SceneNode::SceneNode()
	: parent(nullptr)
	, children()
{
}

void SceneNode::attachChild(NodePointer child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::NodePointer SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&](NodePointer& p) { return p.get() == &node; });
	assert(found != children.end());

	NodePointer result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for(NodePointer & child: children)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const NodePointer& child : children)
		child->draw(target, states);
}
