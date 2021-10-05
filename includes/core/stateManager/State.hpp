#pragma once
#include "StateControls.hpp"

#include <cstdint>


namespace Yuna
{
	namespace Core
	{
		class State
		{
		protected:
			eStateControls	mStateAction = eStateControls::PREVIOUS_STATE;
			uint8_t			mNextState = 0;
		public:
			State(/* args */);
			virtual ~State();

			void			Run();

			//Getters
			eStateControls	GetStateAction() {return (mStateAction);}
			uint8_t			GetNextState() {return (mNextState);}
		};
	} // namespace name
} // namespace Yuna



