#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;

	struct Rectangle
	{
		Position2D position;
		Vector2D size;
	};

	struct Circle
	{
		Position2D position;
		float radius;
	};

	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2);
	bool DoShapesCollide(const Circle& circle1, const Circle& circle2);
	bool DoShapesCollide(const Rectangle& rect, const Circle& circle);

	Position2D GetRandomPostionInRectangle(const Rectangle& rect);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	//Help method to orginise text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, //Left or Top
		Middle,
		Max  //Right or Bottom
	};

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
}
