/*
 * File: EventHandler.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:19:03 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 19th October 2021 10:17:42 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "EventHandler.hpp"

namespace Yuna
{
	namespace Core
	{
		EventHandler::EventHandler()
		{
		}

		EventHandler::~EventHandler()
		{
		}

		void EventHandler::HandleEvent(sf::Event &tEvent)
		{
			mf::GUI::HandleEvent(tEvent);
			switch (tEvent.type)
			{
			case sf::Event::KeyPressed:
				if (mBindingMap.count(tEvent.key.code))
					mEventStates[mBindingMap[tEvent.key.code]] = true;
				break;
			case sf::Event::KeyReleased:
				if (mBindingMap.count(tEvent.key.code))
					mEventStates[mBindingMap[tEvent.key.code]] = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (mBindingMap.count(tEvent.key.code + EVENTHANDLER_BUTTON_OFFSET))
					mEventStates[mBindingMap[tEvent.key.code + EVENTHANDLER_BUTTON_OFFSET]] = true;
				break;
			case sf::Event::MouseButtonReleased:
				if (mBindingMap.count(tEvent.key.code + EVENTHANDLER_BUTTON_OFFSET))
					mEventStates[mBindingMap[tEvent.key.code + EVENTHANDLER_BUTTON_OFFSET]] = false;
				break;
			default:
				break;
			}
		}

		void EventHandler::BindKey(sf::Keyboard::Key tKey, uint32_t tEvent)
		{
			mBindingMap[(u_int32_t)tKey] = tEvent;
		}

		void EventHandler::BindButton(sf::Mouse::Button tButton, uint32_t tEvent)
		{
			mBindingMap[((u_int32_t)tButton) + EVENTHANDLER_BUTTON_OFFSET] = tEvent;
		}

		void EventHandler::SetEventState(uint32_t tEvent, bool tState)
		{
			mEventStates[tEvent] = tState;
		}

		bool EventHandler::GetEventState(uint32_t tEvent)
		{
			return (mEventStates[tEvent]);
		}
	} // namespace Core
} // namespace Yuna
