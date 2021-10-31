/*
 * File: Collisions.hpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:57:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 30th October 2021 12:38:56 pm
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
	} // namespace Physics
} // namespace Yuna


