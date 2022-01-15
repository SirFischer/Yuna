/*
 * File: State.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 13th January 2022 7:06:22 am
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
			float		frameTime = 0.f;
			while (mActive)
			{
				while (mElapsedTime >= mDeltaTime)
				{
					HandleEvents();
					Update();
					mElapsedTime -= mDeltaTime;
				}
				Render();
				frameTime = gameLoopClock.restart().asSeconds();
				mSmoothFrameTime = (mSmoothFrameTime * mFPSSmoothing) + ((frameTime * (1.f - mFPSSmoothing)));
				mFPS = 1.f / mSmoothFrameTime;
				mFrameTime = frameTime;
				mElapsedTime += frameTime;
			}
		}

		void	State::SetDeltaTime(const float &tDeltaTime)
		{
			mDeltaTime = tDeltaTime;
		}
	}
}
