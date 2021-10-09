#include "EventHandler.hpp"

namespace Yuna
{
	namespace Core
	{
		EventHandler::EventHandler(Window* tWindow)
		{
			mWindow = tWindow;
		}

		EventHandler::~EventHandler()
		{
		}

		void		EventHandler::HandleEvent()
		{
			sf::Event event;
			while (mWindow->PollEvent(event))
			{
				mf::GUI::HandleEvent(event);
				//Handle event
			}
		}
	} // namespace Core
} // namespace Yuna
