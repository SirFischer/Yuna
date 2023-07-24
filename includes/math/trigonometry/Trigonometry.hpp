/*
 * File: Trigonometry.hpp
 * Project: Extermination
 * File Created: Saturday, 28th May 2022 8:40:08 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 28th May 2022 8:52:36 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include <math.h>

#include <SFML/Graphics.hpp>

namespace Yuna
{
	namespace Math
	{
		float	Distance(const sf::Vector2f &pPoint_1, const sf::Vector2f &pPoint_2);
		float	Angle(const sf::Vector2f &pPoint_1, const sf::Vector2f &pPoint_2);
	}
}