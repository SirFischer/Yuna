#pragma once
#include "StateControls.hpp"
#include "../Window.hpp"
#include "../eventHandler/EventHandler.hpp"
#include "../resourceManager/ResourceManager.hpp"
#include "../console/Console.hpp"

#include <SFML/System/Clock.hpp>

#include <cstdint>


namespace Yuna
{
	namespace Core
	{
		class State
		{
		protected:
			Window*			mWindow;
			EventHandler	mEventHandler;
			ResourceManager	mResourceManager;
			eStateControls	mStateAction = eStateControls::PREVIOUS_STATE;
			uint8_t			mNextState = 0;
			bool			mActive = true;
			float			mDeltaTime = 1.f / 60.f;
			float			mFPSSmoothing = 0.9;
			float			mFPS = 0;

			virtual void	Render() = 0;
			virtual void	Update() = 0;
			virtual void	HandleEvents() = 0;
		public:
			State(Window*	tWindow);
			virtual ~State();

			void			Run();

			virtual void	Init() = 0;

			//Setters
			void			SetDeltaTime(const float &tDeltaTime);

			//Getters
			eStateControls	GetStateAction() {return (mStateAction);}
			uint8_t			GetNextState() {return (mNextState);}
			float			GetDeltaTime() {return (mDeltaTime);}

		};
	} // namespace name
} // namespace Yuna



