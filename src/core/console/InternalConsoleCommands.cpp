/*
 * File: InternalConsoleCommands.cpp
 * Folder: Console
 * File Created: Thursday, 4th March 2021 6:11:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 8:58:06 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic, Deep Vertic
 */

#include "Console.hpp"

namespace Yuna
{
	namespace Core
	{
		Console::eCommandStatus Help(const std::vector<std::string> &tParams)
		{
			if (tParams.size() == 0)
			{
				Console::AddString("Available commands:");
				for (auto &command : Console::GetCommands())
				{
					Console::AddString(command.first + " - " + command.second.mHelpShort);
				}
			}
			else
			{
				for (auto &command : tParams)
				{
					if (Console::GetCommands().count(command))
						Console::AddString(command + " - " + Console::GetCommands()[command].mHelpLong);
					else
						Console::AddString(command + " does not exist...");
				}
			}
			return (Console::eCommandStatus::SUCCESS);
		}

		Console::eCommandStatus Clear(const std::vector<std::string> &tParams)
		{
			(void)tParams;
			Console::ClearConsole();
			return (Console::eCommandStatus::SUCCESS);
		}

		Console::eCommandStatus BindKey(const std::vector<std::string> &tParams)
		{
			if (!Console::mEventHandler)
			{
				Console::AddString("No event handler set!");
				return (Console::eCommandStatus::FAILURE);
			}
			if (!Console::mActionNames)
			{
				Console::AddString("No action name library provided!");
				return (Console::eCommandStatus::FAILURE);
			}
			if (tParams.size() != 2)
			{
				Console::AddString("Usage: bindkey <key> <command>");
				return (Console::eCommandStatus::BAD_ARGUMENTS);
			}
			int32_t key = -1;
			int32_t action = -1;
			for (auto k : Console::mEventHandler->GetBindingNames())
			{
				if (k.second == tParams[0])
				{
					key = k.first;
					break;
				}
			}
			for (auto a : *Console::mActionNames)
			{
				if (a.second == tParams[1])
				{
					action = a.first;
					break;
				}
			}
			if (key != -1 && action != -1)
			{
				if (key < EVENTHANDLER_BUTTON_OFFSET)
					Console::mEventHandler->BindKey((sf::Keyboard::Key)key, action);
				else if (key < EVENTHANDLER_WHEEL_OFFSET - 10)
					Console::mEventHandler->BindButton((sf::Mouse::Button)(key - 1000), action);
				else if (key == EVENTHANDLER_WHEEL_OFFSET + 1)
					Console::mEventHandler->BindWheelUp(action);
				else if (key == EVENTHANDLER_WHEEL_OFFSET - 1)
					Console::mEventHandler->BindWheelDown(action);
			}
			else
			{
				Console::AddString("The key or action is wrong...");
				return (Console::eCommandStatus::BAD_ARGUMENTS);
			}
			return (Console::eCommandStatus::SUCCESS);
		}

		void Console::LoadInternalCommands()
		{
			AddCommand((sCommand){.mFunction = Help,
								  .mHelpShort = "List available commands.",
								  .mHelpLong = "List available commands. Use help [command] to get more information about the command."},
					   "help");
			AddCommand((sCommand){.mFunction = Clear,
								  .mHelpShort = "Clears the console.",
								  .mHelpLong = "Clears the console... that's it!"},
					   "clear");
			AddCommand((sCommand){.mFunction = BindKey,
								  .mHelpShort = "Binds a new key to an action",
								  .mHelpLong = "Use bind [key] [action] to bind a key.\n Example: bind A move_left"},
						"bind");
		}

	}
}