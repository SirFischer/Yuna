#include "StateManager.hpp"

namespace Yuna
{
	namespace Core
	{
		StateManager::StateManager(Window *tWindow)
		{
			mWindow = tWindow;
		}

		StateManager::~StateManager()
		{
			
		}

		void	StateManager::HandleStateAction()
		{
			eStateControls	action = mStateStack.top()->GetStateAction();
			uint8_t			nextState = mStateStack.top()->GetNextState();
			switch(action)
			{
				//Pops every state except for the last one
				case eStateControls::BACK_TO_ENTRY:
					while (mStateStack.size() - 1)
						mStateStack.pop();
				break;
				case eStateControls::PREVIOUS_STATE:
					mStateStack.pop();
				break;
				case eStateControls::NEXT_STATE:
					mStateStack.push(mStateFactory(nextState, mWindow));
				break;
				case eStateControls::REPLACE_STATE:
					mStateStack.pop();
					mStateStack.push(mStateFactory(nextState, mWindow));
				break;
				case eStateControls::EXIT:
					while (mStateStack.size())
						mStateStack.pop();
				break;
				default:
					//what to do here?
				break;
			}
		}

		void	StateManager::SetStateFactory(const StateFactory &tStateFactory)
		{
			mStateFactory = tStateFactory;
		}


		void	StateManager::SetEntryState(const uint8_t &tStateID)
		{
			mStateStack.push(mStateFactory(tStateID, mWindow));
		}

		void	StateManager::Run()
		{
			if (mStateStack.empty())
				throw std::runtime_error("StateManager missing entry state");
			while (!mStateStack.empty())
			{
				mStateStack.top()->Run();
				HandleStateAction();
			}
		}
	} // namespace core
} // namespace name