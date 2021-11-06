/*
 * File: Collisions.cpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:58:27 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 8:13:25 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Collisions.hpp"
namespace Yuna
{
	namespace Physics
	{
		bool	AABBCollision(const sf::FloatRect &pRect1, const sf::FloatRect &pRect2)
		{
			return (pRect1.left < pRect2.left + pRect2.width &&
					pRect1.left + pRect1.width > pRect2.left &&
					pRect1.top < pRect2.top + pRect2.height &&
					pRect1.top + pRect1.height > pRect2.top);
		}

		bool	LineLineCollision(const sf::Vector2f &pLine1Start, const sf::Vector2f &pLine1End, const sf::Vector2f &pLine2Start, const sf::Vector2f &pLine2End)
		{
			float uA = ((pLine2End.x - pLine2Start.x) * (pLine1Start.y - pLine2Start.y) - (pLine2End.y - pLine2Start.y) * (pLine1Start.x - pLine2Start.x)) /
				((pLine2End.y - pLine2Start.y) * (pLine1End.x - pLine1Start.x) - (pLine2End.x - pLine2Start.x) * (pLine1End.y - pLine1Start.y));
			float uB = ((pLine1End.x - pLine1Start.x) * (pLine1Start.y - pLine2Start.y) - (pLine1End.y - pLine1Start.y) * (pLine1Start.x - pLine2Start.x)) /
				((pLine2End.y - pLine2Start.y) * (pLine1End.x - pLine1Start.x) - (pLine2End.x - pLine2Start.x) * (pLine1End.y - pLine1Start.y));
			if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
				return true;
			return (false);
		}

		bool	LineRectCollision(const sf::Vector2f &pLineStart, const sf::Vector2f &pLineEnd, const sf::FloatRect &pRect)
		{
			bool	left = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top), sf::Vector2f(pRect.left, pRect.top + pRect.height));
			bool	right = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left + pRect.width, pRect.top), sf::Vector2f(pRect.left + pRect.width, pRect.top + pRect.height));
			bool	top = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top), sf::Vector2f(pRect.left + pRect.width, pRect.top));
			bool	bottom = LineLineCollision(pLineStart, pLineEnd, sf::Vector2f(pRect.left, pRect.top + pRect.height), sf::Vector2f(pRect.left + pRect.width, pRect.top + pRect.height));

			return (left || right || top || bottom);
		}
	} // namespace Physics
} // namespace Yuna