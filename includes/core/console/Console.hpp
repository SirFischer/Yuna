/*
 * File: Console.hpp
 * Project: Extermination
 * File Created: Wednesday, 20th October 2021 7:29:46 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 28th October 2021 6:26:34 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include <functional>
#include <map>
#include <vector>
#include <sstream>
#include <deque>

#include "mfGUI.hpp"

namespace Yuna
{
	namespace Core
	{

		class Console
		{
		public:
			enum class eCommandStatus
			{
				SUCCESS,
				FAILURE,
				BAD_COMMAND,
				BAD_ARGUMENTS
			};
			typedef std::function<Console::eCommandStatus(const std::vector<std::string> &tParams)> tCommandFunction;
			struct sCommand
			{
				Console::tCommandFunction mFunction;
				std::string mHelpShort;
				std::string mHelpLong;
			};

		private:
			Console(/* args */) {}
			~Console() {}

			/**
			 * GUI
			 **/
			static mf::Container *mConsoleWidget;
			static mf::Text *mConsoleTextBox;
			static mf::Text *mConsoleInputBox;

			/**
			 * Data
			 **/
			static bool mProccessing;
			static std::map<std::string, sCommand>	mCommands;
			static std::deque<std::string>			mHistory;
			static size_t							mHistorySize;
			static int								mHistoryIndex;

			static void LoadInternalCommands();

		public:
			static void Init();
			static void InitUI();
			static void ToggleConsole();

			static void AddCommand(sCommand tCommand, const std::string &tCommandName);

			static eCommandStatus ProcessCommand(std::string tCommand);
			static void	ProcessConsoleCommand();

			static void Update();

			static void AddString(const std::string &tMessage);
			static void ClearConsole();

			static void GetNextInCommandHistory();
			static void GetPreviousInCommandHistory();

			/**
	 		* GETTERS
	 		**/
			static std::map<std::string, sCommand> &GetCommands() { return (mCommands); }
			static bool IsOpen() { return (!mConsoleWidget->IsDisabled()); }


		};

	} // namespace Core

} // namespace Yuna
