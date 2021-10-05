#pragma once

#include "../Window.hpp"

namespace Yuna
{
	namespace Core
	{
		class EventHandler
		{
		private:
			Window*		mWindow;
		public:
			EventHandler(Window* tWindow);
			~EventHandler();

			void		HandleEvent();
		};
	} // namespace Core
	
} // namespace Yuna



