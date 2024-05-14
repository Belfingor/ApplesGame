#include "Apple.h"
#include "Game.h"



namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		//Init Apple Sprite
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void SetApplePosition(Apple& apple, const Position2D& position)
	{
		apple.position = position;
	}

	Circle GetAppleCollider(const Apple& apple)
	{
		return { apple.position, APPLE_SIZE / 2.f };
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isAppleEaten)
		{
			apple.position.x = -10.f;
			apple.position.y = -10.f;
			return;
		}
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);
	}
	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isAppleEaten = true;
	}
}