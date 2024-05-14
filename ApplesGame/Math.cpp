#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	bool DoShapesCollide(const Rectangle& rect1, const Rectangle& rect2)
	{
		return rect1.position.x < rect2.position.x + rect2.size.x &&
			rect1.position.x + rect1.size.x > rect2.position.x &&
			rect1.position.y < rect2.position.y + rect2.size.y &&
			rect1.position.y + rect1.size.y > rect2.position.y;
	}
	bool DoShapesCollide(const Circle& circle1, const Circle& circle2)
	{
		float dx = circle1.position.x - circle2.position.x;
		float dy = circle1.position.y - circle2.position.y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance < circle1.radius + circle2.radius;
	}
	bool DoShapesCollide(const Rectangle& rect, const Circle& circle)
	{
		float dx = circle.position.x - std::max(rect.position.x, std::min(circle.position.x, rect.position.x + rect.size.x));
		float dy = circle.position.y - std::max(rect.position.y, std::min(circle.position.y, rect.position.y + rect.size.y));
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}
	Position2D GetRandomPostionInRectangle(const Rectangle& rect)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * rect.size.x + rect.position.x;
		result.y = rand() / (float)RAND_MAX * rect.size.y + rect.position.y;
		return result;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	//fixing sprite hitbox
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect totalRect;
		//Calculate total width/height of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect itemRect = (*it)->getGlobalBounds();

			if (orientation == Orientation::Horizontal)
			{
				totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
				totalRect.height = std::max(totalRect.height, itemRect.height);
			}
			else
			{
				totalRect.width = std::max(totalRect.width, itemRect.width);
				totalRect.height = itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
			}

			totalRect.left = position.x - origin.x * totalRect.width;
			totalRect.top = position.y - origin.y * totalRect.height;
			sf::Vector2f currentPos = { totalRect.left, totalRect.top };

			for (auto it = items.begin(); it != items.end(); ++it)
			{
				sf::FloatRect itemRect = (*it)->getGlobalBounds();
				sf::Vector2f itemOrigin;

				if (orientation == Orientation::Horizontal)
				{
					itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
					itemOrigin.x = 0;
					currentPos.y = totalRect.top, +itemOrigin.y * totalRect.height;
				}
				else
				{
					itemOrigin.y = 0.f;
					itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
					currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
				}

				(*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
				(*it)->setPosition(currentPos);
				window.draw(**it);

				if (orientation == Orientation::Horizontal)
				{
					currentPos.x += itemRect.width + spacing;
				}
				else
				{
					currentPos.y += itemRect.height + spacing;
				}
			}
		}
	}

}