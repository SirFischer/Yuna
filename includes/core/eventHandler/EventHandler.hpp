/*
 * File: EventHandler.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 9:57:02 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 10:47:00 pm
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
			typedef std::map<uint32_t, std::string>	tBindingNames;

			tEventStateList	mEventStates;
			tBindingMapList	mBindingMap;
			tBindingNames	mBindingNames;

			void			InitBindingNames();

		public:
			EventHandler();
			~EventHandler();

			void			HandleEvent(sf::Event &pEvent); 

			void			BindKey(sf::Keyboard::Key pKey, uint32_t pEvent);
			void			BindButton(sf::Mouse::Button pButton, uint32_t pEvent);
			void			SetEventState(uint32_t pEvent, bool tState);
			bool			GetEventState(uint32_t pEvent);

			tBindingMapList	GetBindingMap(){ return (mBindingMap); }
			tBindingNames	GetBindingNames(){ return (mBindingNames); }
		};
	} // namespace Core
	
} // namespace Yuna



