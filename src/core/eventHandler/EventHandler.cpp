/*
 * File: EventHandler.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:19:03 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 9:04:36 pm
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
			InitBindingNames();
		}

		EventHandler::~EventHandler()
		{
		}

		void EventHandler::HandleEvent(sf::Event &pEvent)
		{
			mf::GUI::HandleEvent(pEvent);
			switch (pEvent.type)
			{
			case sf::Event::KeyPressed:
				if (mBindingMap.count(pEvent.key.code))
					mEventStates[mBindingMap[pEvent.key.code]] = true;
				break;
			case sf::Event::KeyReleased:
				if (mBindingMap.count(pEvent.key.code))
					mEventStates[mBindingMap[pEvent.key.code]] = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (mBindingMap.count(pEvent.key.code + EVENTHANDLER_BUTTON_OFFSET))
					mEventStates[mBindingMap[pEvent.key.code + EVENTHANDLER_BUTTON_OFFSET]] = true;
				break;
			case sf::Event::MouseButtonReleased:
				if (mBindingMap.count(pEvent.key.code + EVENTHANDLER_BUTTON_OFFSET))
					mEventStates[mBindingMap[pEvent.key.code + EVENTHANDLER_BUTTON_OFFSET]] = false;
				break;
			 case sf::Event::MouseWheelScrolled:
			 	if (mBindingMap.count(EVENTHANDLER_WHEEL_OFFSET + pEvent.mouseWheelScroll.delta))
			 		mEventStates[mBindingMap[EVENTHANDLER_WHEEL_OFFSET + pEvent.mouseWheelScroll.delta]] = true;
			 	break;
			case sf::Event::MouseMoved:
				mMousePosition = { (float)pEvent.mouseMove.x, (float)pEvent.mouseMove.y };
			default:
				break;
			}
		}

		void EventHandler::BindKey(sf::Keyboard::Key pKey, uint32_t pEvent)
		{
			ClearEventBinding(pEvent);
			mBindingMap[(u_int32_t)pKey] = pEvent;
		}

		void EventHandler::BindButton(sf::Mouse::Button pButton, uint32_t pEvent)
		{
			ClearEventBinding(pEvent);
			mBindingMap[((u_int32_t)pButton) + EVENTHANDLER_BUTTON_OFFSET] = pEvent;
		}

		void			EventHandler::BindWheelDown(uint32_t pEvent)
		{
			ClearEventBinding(pEvent);
			mBindingMap[EVENTHANDLER_WHEEL_OFFSET - 1] = pEvent;
		}

		void			EventHandler::BindWheelUp(uint32_t pEvent)
		{
			ClearEventBinding(pEvent);
			mBindingMap[EVENTHANDLER_WHEEL_OFFSET + 1] = pEvent;
		}


		void EventHandler::SetEventState(uint32_t pEvent, bool pState)
		{
			mEventStates[pEvent] = pState;
		}

		bool EventHandler::GetEventState(uint32_t pEvent)
		{
			return (mEventStates[pEvent]);
		}

		void EventHandler::ClearEventBinding(uint32_t pEvent)
		{
			for (auto &binding : mBindingMap)
			{
				if (binding.second == pEvent)
				{
					mBindingMap.erase(binding.first);
					break;
				}
			}
		}

	} // namespace Core
} // namespace Yuna
