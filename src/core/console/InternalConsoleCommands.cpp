/*
 * File: InternalConsoleCommands.cpp
 * Folder: Console
 * File Created: Thursday, 4th March 2021 6:11:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 4th November 2021 7:09:15 am
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
			if (tParams.size() != 2)
			{
				Console::AddString("Usage: bindkey <key> <command>");
				return (Console::eCommandStatus::BAD_ARGUMENTS);
			}
			//Implement key binding dictionary
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
		}

	}
}