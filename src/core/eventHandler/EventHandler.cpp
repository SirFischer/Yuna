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
			mWindow->PollEvent(event);
			//Handle event
		}

	} // namespace Core
} // namespace Yuna
