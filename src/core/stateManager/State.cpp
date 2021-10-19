/*
 * File: State.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 19th October 2021 10:19:43 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "State.hpp"

namespace Yuna
{
	namespace Core
	{
		State::State(Window* tWindow)
		{
			mWindow = tWindow;
		}

		State::~State()
		{

		}

		void	State::Run()
		{
			sf::Clock	gameLoopClock;
			//may need to make this a member in case someone want to switch it while running, although i don't know why that would be usefull...
			float		mElapsedTime = 0.f;
			while (mActive)
			{
				while (mElapsedTime >= mDeltaTime)
				{
					HandleEvents();
					Update();
					mElapsedTime -= mDeltaTime;
				}
				Render();
				mElapsedTime += gameLoopClock.restart().asSeconds();
			}
		}

		void	State::SetDeltaTime(const float &tDeltaTime)
		{
			mDeltaTime = tDeltaTime;
		}

	}
}
