#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Game;

	struct Apple
	{
		Position2D position;

		//Resources
		sf::Sprite sprite;

		bool isAppleEaten = false;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void SetApplePosition(Apple& apple, const Position2D& position);
	Circle GetAppleCollider(const Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void MarkAppleAsEaten(Apple& apple);

}