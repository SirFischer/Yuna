/*
 * File: InternalConsoleCommands.cpp
 * Folder: Console
 * File Created: Thursday, 4th March 2021 6:11:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 11:07:16 am
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