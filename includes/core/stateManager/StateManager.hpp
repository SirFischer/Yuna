#pragma once
#include "State.hpp"

#include <string>
#include <map>
#include <stack>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>
#include <cstdint>

namespace Yuna
{
	namespace Core
	{
		typedef std::function<std::unique_ptr<State>(uint8_t)> StateFactory;
		class StateManager
		{
		private:
			std::stack<std::unique_ptr<State>>		mStateStack;

			StateFactory			mStateFactory;

			void					HandleStateAction();

		public:
			StateManager();
			~StateManager();

			void					SetStateFactory(const StateFactory &tStateFactory);
			void					SetEntryState(const uint8_t &tStateID);

			void					Run();
		};
	} // namespace core
} // namespace Yuna



