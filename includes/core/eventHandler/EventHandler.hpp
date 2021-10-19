/*
 * File: EventHandler.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 19th October 2021 10:17:56 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#pragma once

#include "../Window.hpp"
#include <map>
#include <functional>

#define EVENTHANDLER_BUTTON_OFFSET 1000

namespace Yuna
{
	namespace Core
	{
		class EventHandler
		{
		private:
			typedef std::map<uint32_t, bool>		tEventStateList;
			typedef std::map<uint32_t, uint32_t>	tBindingMapList;

			tEventStateList	mEventStates;
			tBindingMapList	mBindingMap;

		public:
			EventHandler();
			~EventHandler();

			void			HandleEvent(sf::Event &tEvent); 

			void			BindKey(sf::Keyboard::Key tKey, uint32_t tEvent);
			void			BindButton(sf::Mouse::Button tButton, uint32_t tEvent);
			void			SetEventState(uint32_t tEvent, bool tState);
			bool			GetEventState(uint32_t tEvent);
		};
	} // namespace Core
	
} // namespace Yuna



