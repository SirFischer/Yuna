/*
 * File: Object.cpp
 * Project: Extermination
 * File Created: Saturday, 4th June 2022 7:34:02 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 4th June 2022 7:52:18 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Object.hpp"

namespace Yuna
{
	namespace World
	{
		void	Object::TakeDamage(float pDamage)
		{
			mHealth -= std::abs(pDamage);
		}
		
	} // namespace World
	
} // namespace Yuna
