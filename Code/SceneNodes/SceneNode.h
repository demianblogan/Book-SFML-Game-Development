#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

struct Command;

// Everything in the game is drawn by node system. So if your class
// should be drawn on the window - it must be a scene node. Node system
// contains nodes, the structure inside the system is simple tree:
// every node has only one parent node and any number of children nodes.
// Tree system allows us to draw nodes by priority: first the most parent
// nodes are drawn, next is their children. Also every node has basic
// transofming functionality from SFML due to us using this library for rendering.
// SceneNode is a class that represent a node of this system.
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	using NodePointer = std::unique_ptr<SceneNode>;

	enum class Category : unsigned int
	{
		None           = 0,
		Scene          = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft  = 1 << 3
	};

private:
	SceneNode* parent = nullptr;
	std::vector<NodePointer> children;

	virtual void UpdateCurrent(sf::Time deltaTime);
	void UpdateChildren(sf::Time deltaTime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	void Update(sf::Time deltaTime);

	sf::Transform GetWorldTransform() const;
	sf::Vector2f GetWorldPosition() const;
	virtual unsigned int GetCategory() const;

	void OnCommand(const Command& command, sf::Time deltaTime);

	void AttachChild(NodePointer child);
	NodePointer DetachChild(const SceneNode& node);
};