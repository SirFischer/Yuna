/*
 * File: EventHandler.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 8:31:22 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#pragma once

#include "../Window.hpp"
#include <map>
#include <functional>

#define EVENTHANDLER_BUTTON_OFFSET 1000
#define EVENTHANDLER_WHEEL_OFFSET 2000

namespace Yuna
{
	namespace Core
	{
		class EventHandler
		{
		private:
			typedef std::map<uint32_t, bool>		tEventStateList;
			typedef std::map<uint32_t, uint32_t>	tBindingMapList;
			typedef std::map<uint32_t, std::string>	tBindingNames;

			tEventStateList	mEventStates;
			tBindingMapList	mBindingMap;
			tBindingNames	mBindingNames;

			sf::Vector2f	mMousePosition;

			void			InitBindingNames();

			void			ClearEventBinding(uint32_t pEvent);

		public:
			EventHandler();
			~EventHandler();

			void			HandleEvent(sf::Event &pEvent); 

			void			BindKey(sf::Keyboard::Key pKey, uint32_t pEvent);
			void			BindButton(sf::Mouse::Button pButton, uint32_t pEvent);
			void			BindWheelDown(uint32_t pEvent);
			void			BindWheelUp(uint32_t pEvent);
			void			SetEventState(uint32_t pEvent, bool tState);
			bool			GetEventState(uint32_t pEvent);
			sf::Vector2f	GetMousePosition() const { return mMousePosition; }

			tBindingMapList	GetBindingMap(){ return (mBindingMap); }
			tBindingNames	GetBindingNames(){ return (mBindingNames); }
		};
	} // namespace Core
	
} // namespace Yuna



