/*
 * File: Trigonometry.cpp
 * Project: Extermination
 * File Created: Saturday, 28th May 2022 8:45:05 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 28th May 2022 8:56:15 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Trigonometry.hpp"

namespace Yuna
{
	namespace Math
	{
		float	Distance(const sf::Vector2f &pPoint_1, const sf::Vector2f &pPoint_2)
		{
			return (sqrt((pow(pPoint_1.x - pPoint_2.x, 2.f) + pow(pPoint_1.y - pPoint_2.y, 2.f))));
		}
	}

}