#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, const sf::Texture& texture)
	{
		// Init player state
		SetPlayerPosition(player, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		SetPlayerSpeed(player, INITIAL_SPEED);
		SetPlayerDirection(player, PlayerDirection::Right);

		// Init Player Sprite
		player.sprite.setTexture(texture);
		SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void SetPlayerDirection(Player& player, PlayerDirection direction)
	{
		player.direction = direction;
	}

	void SetPlayerPosition(Player& player, const Position2D& position)
	{
		player.position = position;
	}

	void SetPlayerSpeed(Player& player, float speed)
	{
		player.speed = speed;
	}

	float GetPlayerSpeed(const Player& player)
	{
		return player.speed;
	}

	Rectangle GetPlayerCollider(const Player& player)
	{
		return { { player.position.x - PLAYER_SIZE / 2.f, player.position.y - PLAYER_SIZE / 2.f },
			{ PLAYER_SIZE, PLAYER_SIZE } };
	}

	void UpdatePlayer(Player& player, float deltaTime)
	{
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * deltaTime;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * deltaTime;
			break;
		}
		}
	}


	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);

		if (player.direction == PlayerDirection::Left)
		{
			SetSpriteSize(player.sprite, -PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
		}
		else
		{
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation((float)player.direction * -90.f);
		}
	}
}

