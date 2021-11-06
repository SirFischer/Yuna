/*
 * File: Collisions.hpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:57:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 8:11:27 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>

namespace Yuna
{
	namespace Physics
	{
		bool	AABBCollision(const sf::FloatRect &pRect1, const sf::FloatRect &pRect2);
		bool	LineLineCollision(const sf::Vector2f &pLine1Start, const sf::Vector2f &pLine1End, const sf::Vector2f &pLine2Start, const sf::Vector2f &pLine2End);
		bool	LineRectCollision(const sf::Vector2f &pLineStart, const sf::Vector2f &pLineEnd, const sf::FloatRect &pRect);
	} // namespace Physics
} // namespace Yuna


