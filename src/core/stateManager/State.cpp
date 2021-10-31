/*
 * File: State.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 30th October 2021 11:30:51 pm
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
			float		mFrameTime = 0.f;
			while (mActive)
			{
				while (mElapsedTime >= mDeltaTime)
				{
					HandleEvents();
					Update();
					mElapsedTime -= mDeltaTime;
				}
				Render();
				mFrameTime = gameLoopClock.restart().asSeconds();
				mFPS = (mFPS * mFPSSmoothing) + (mFrameTime * (1.f - mFPSSmoothing));
				mElapsedTime += mFrameTime;
			}
		}

		void	State::SetDeltaTime(const float &tDeltaTime)
		{
			mDeltaTime = tDeltaTime;
		}

	}
}
