/*
 * File: Collisions.hpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:57:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 11:37:57 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

namespace Yuna
{
	namespace Physics
	{
		bool	AABBCollision(const sf::FloatRect &pRect1, const sf::FloatRect &pRect2);
		bool	LineLineCollision(const sf::Vector2f &pLine1Start, const sf::Vector2f &pLine1End, const sf::Vector2f &pLine2Start, const sf::Vector2f &pLine2End);
		bool	LineRectCollision(const sf::Vector2f &pLineStart, const sf::Vector2f &pLineEnd, const sf::FloatRect &pRect);
		bool	RayRectCollision(const sf::Vector2f &pRayStart, const sf::Vector2f &pRayDir, const sf::FloatRect &pRect, sf::Vector2f &pContactPoint, sf::Vector2f &pContactNormal, float &pNearTime);
		bool	DynamicRectCollision(const sf::FloatRect &pRect1, const sf::Vector2f &pVelocity, const sf::FloatRect &pRect2, sf::Vector2f &pContactPoint, sf::Vector2f &pContactNormal, float &pNearTime);
	} // namespace Physics
} // namespace Yuna


