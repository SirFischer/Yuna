/*
 * File: Collisions.cpp
 * Project: Extermination
 * File Created: Saturday, 30th October 2021 9:58:27 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 30th October 2021 12:39:26 pm
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
	} // namespace Physics
} // namespace Yuna