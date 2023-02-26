/*
 * File: Object.hpp
 * Project: Extermination
 * File Created: Saturday, 4th June 2022 7:31:03 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 18th February 2023 2:53:25 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include <math.h>

namespace Yuna
{
	namespace World
	{
		class Object
		{
		protected:
			float	mMaxHealth = 100.f;
			float	mHealth = 100.f;

		public:
			virtual ~Object() {};

			virtual void	TakeDamage(float pDamage);

			float			GetHealth(){return (mHealth);}
		};

		
	} // namespace World
} // namespace Yuna