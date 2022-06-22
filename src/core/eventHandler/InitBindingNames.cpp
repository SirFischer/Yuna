/*
 * File: InitBindingNames.cpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 9:14:27 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 8:41:18 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "EventHandler.hpp"

namespace Yuna
{
	namespace Core
	{
		void		EventHandler::InitBindingNames()
		{
			mBindingNames[sf::Keyboard::A] = "A";
			mBindingNames[sf::Keyboard::B] = "B";
			mBindingNames[sf::Keyboard::C] = "C";
			mBindingNames[sf::Keyboard::D] = "D";
			mBindingNames[sf::Keyboard::E] = "E";
			mBindingNames[sf::Keyboard::F] = "F";
			mBindingNames[sf::Keyboard::G] = "G";
			mBindingNames[sf::Keyboard::H] = "H";
			mBindingNames[sf::Keyboard::I] = "I";
			mBindingNames[sf::Keyboard::J] = "J";
			mBindingNames[sf::Keyboard::K] = "K";
			mBindingNames[sf::Keyboard::L] = "L";
			mBindingNames[sf::Keyboard::M] = "M";
			mBindingNames[sf::Keyboard::N] = "N";
			mBindingNames[sf::Keyboard::O] = "O";
			mBindingNames[sf::Keyboard::P] = "P";
			mBindingNames[sf::Keyboard::Q] = "Q";
			mBindingNames[sf::Keyboard::R] = "R";
			mBindingNames[sf::Keyboard::S] = "S";
			mBindingNames[sf::Keyboard::T] = "T";
			mBindingNames[sf::Keyboard::U] = "U";
			mBindingNames[sf::Keyboard::V] = "V";
			mBindingNames[sf::Keyboard::W] = "W";
			mBindingNames[sf::Keyboard::X] = "X";
			mBindingNames[sf::Keyboard::Y] = "Y";
			mBindingNames[sf::Keyboard::Z] = "Z";
			mBindingNames[sf::Keyboard::Enter] = "Enter";
			mBindingNames[sf::Keyboard::Space] = "Space";
			mBindingNames[sf::Keyboard::Backspace] = "Backspace";
			mBindingNames[sf::Keyboard::Tab] = "Tab";
			mBindingNames[sf::Keyboard::Up] = "Arrow Up";
			mBindingNames[sf::Keyboard::Down] = "Arrow Down";
			mBindingNames[sf::Keyboard::Left] = "Arrow Left";
			mBindingNames[sf::Keyboard::Right] = "Arrow Right";

			mBindingNames[sf::Mouse::Left + EVENTHANDLER_BUTTON_OFFSET]  = "Left Mouse Button";
			mBindingNames[sf::Mouse::Right + EVENTHANDLER_BUTTON_OFFSET]  = "Right Mouse Button";
			mBindingNames[sf::Mouse::Middle + EVENTHANDLER_BUTTON_OFFSET]  = "Middle Mouse Button";

			mBindingNames[EVENTHANDLER_WHEEL_OFFSET + 1] = "Mouse Wheel Up";
			mBindingNames[EVENTHANDLER_WHEEL_OFFSET - 1] = "Mouse Wheel Down";


		}
	}
}
