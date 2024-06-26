/*
 * File: Console.cpp
 * Project: Extermination
 * File Created: Wednesday, 20th October 2021 7:28:28 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 23rd May 2022 10:25:42 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Console.hpp"

#include <iomanip>

namespace Yuna
{
	namespace Core
	{

		mf::Container									*Console::mConsoleWidget = NULL;
		mf::Text										*Console::mConsoleTextBox = NULL;
		mf::Text										*Console::mConsoleInputBox = NULL;
		bool											Console::mProccessing = false;
		std::deque<std::string>							Console::mHistory = std::deque<std::string>();
		size_t											Console::mHistorySize = 20;
		int												Console::mHistoryIndex = 0;
		EventHandler									*Console::mEventHandler = NULL;
		std::map<uint32_t, std::string>					*Console::mActionNames = NULL;


		std::map<std::string, Console::sCommand>		Console::mCommands = std::map<std::string, Console::sCommand>();

		void		Console::Init()
		{
			LoadInternalCommands();
		}

		void		Console::InitUI()
		{
			mConsoleWidget = mf::Container::Create();
			mConsoleWidget->SetDisabled(true)
			->SetIndex(1)
			->SetSizePercentage(true, false)->SetSize(100, 500);
			mConsoleWidget->SetBackground(sf::Color(57, 57, 57, 200));
			mf::GUI::AddWidget(mConsoleWidget);

			mConsoleTextBox = mf::Text::Create();
			mConsoleTextBox->SetSizePercentage(true, true)->SetSize(98, 85)
			->SetTextFont("assets/fonts/FiraCode-VariableFont_wght.ttf")
			->SetPositionPercentage(true, true)->SetPosition(1, 1)
			->SetBackgroundColor(sf::Color(37, 37, 37, 200))
			->SetOutlineColor(sf::Color(100, 100, 100, 255))->SetOutlineThickness(1)
			->SetTextPosition(sf::Vector2f(5, 5))
			->SetCharacterSize(14)
			->SetTextColor(sf::Color(255, 255, 255, 255));
			mConsoleTextBox->GetScrollBar()->SetBackgroundColor(sf::Color(37, 37, 37, 200))
			->GetButton()->SetBackground(sf::Color(160, 160, 160, 160));
			mConsoleWidget->AddWidget(mConsoleTextBox);

			mConsoleInputBox = mf::Text::Create();
			mConsoleInputBox->SetSizePercentage(true, false)->SetSize(98, 30)
			->SetTextFont("assets/fonts/FiraCode-VariableFont_wght.ttf")
			->SetPositionPercentage(true, true)->SetPosition(1, 90)
			->SetBackgroundColor(sf::Color(37, 37, 37, 200))
			->SetOutlineColor(sf::Color(100, 100, 100, 255))
			->SetOutlineThickness(1)->SetCharacterSize(12)
			->SetTextPosition(sf::Vector2f(5, 5))
			->SetTextColor(sf::Color(255, 255, 255, 255))
			->EnableEdit();
			mConsoleWidget->AddWidget(mConsoleInputBox);
		}

		void		Console::ToggleConsole()
		{
			mConsoleWidget->SetDisabled(!mConsoleWidget->IsDisabled());
			if (!mConsoleWidget->IsDisabled())
			{
				mHistoryIndex = -1;
				mConsoleInputBox->SetFocus(true);
				mConsoleInputBox->SetText("");
			}
		}

		void		Console::AddCommand(sCommand tCommand, const std::string &tCommandName)
		{
			mCommands[tCommandName] = tCommand;
		}

		Console::eCommandStatus		Console::ProcessCommand(std::string tCommand)
		{
			std::vector<std::string>	parameters;
			std::replace(tCommand.begin(), tCommand.end(), '\t', ' ');
			std::stringstream			ss(tCommand);
			std::string					command;
			std::string					tmp;
			mHistory.push_front(tCommand);
			if (mHistory.size() > mHistorySize)
				mHistory.pop_back();
			ss >> command;
			while (ss >> std::quoted(tmp))
			{
				parameters.push_back(tmp);
			}
			if (mCommands.count(command))
			{
				return (mCommands[command].mFunction(parameters));
			}
			else
			{
				Console::AddString(command + " is not a valid command!");
				return (eCommandStatus::FAILURE);
			}
		}

		Console::eCommandStatus		Console::ProcessFile(const std::string &tFileName)
		{
			std::ifstream				file(tFileName);
			std::string					line;
			bool						comment = false;
			if (file.is_open())
			{
				while (std::getline(file, line))
				{
					if (line.find("/*") != std::string::npos)
						comment = true;
					if (comment)
					{
						if (line.find("*/") != std::string::npos)
							comment = false;
						continue;
					}
					ProcessCommand(line);
				}
				file.close();
				return (eCommandStatus::SUCCESS);
			}
			else
			{
				Console::AddString("Failed to open file: " + tFileName);
				return (eCommandStatus::FAILURE);
			}
		}

		void		Console::WriteBindingsToFile(const std::string &tFileName)
		{
			if (!mEventHandler || !mActionNames)
				return ;
			std::ofstream				file(tFileName);

			if (file.is_open())
			{
				auto map = mEventHandler->GetBindingMap();
				for (auto &binding : map)
				{
					if ((*mActionNames).find(binding.second) != mActionNames->end())
						file << "bind \"" + mEventHandler->GetBindingNames()[binding.first] + "\" " + (*mActionNames)[binding.second] + '\n';
				}
				file.close();
			}
			else
			{
				std::cout << "failed to open file, does it exist?\n";
			}
		}



		void		Console::Update()
		{
			//HANDLE INPUT EVENTS
			if (mProccessing && mConsoleInputBox->IsFocus())
			{
				mProccessing = false;
				std::string command = mConsoleInputBox->GetString();
				if (command.back() == '\n')
					command.pop_back();
				time_t	currentTime = time(NULL);
				std::tm	*ltm = localtime(&currentTime);
				Console::AddString(((ltm->tm_hour <= 9) ? "0" : "") + std::to_string(ltm->tm_hour) + ":" +
									((ltm->tm_min <= 9) ? "0" : "") + std::to_string(ltm->tm_min) + ":" +
									((ltm->tm_sec <= 9) ? "0" : "") + std::to_string(ltm->tm_sec) + " - " + command);
				switch(ProcessCommand(command))
				{
					case eCommandStatus::BAD_ARGUMENTS:
						Console::AddString("Bad arguments, read help manual for how to use this command...");
					break;
					default:
					break;
				}
				mConsoleInputBox->SetText("");
				Console::AddString("");
			}
		}

		void		Console::AddString(const std::string &tMessage)
		{
			mConsoleTextBox->AddText(tMessage + '\n');
		}

		void		Console::ClearConsole()
		{
			mConsoleTextBox->SetText("");
		}

		void		Console::ProcessConsoleCommand()
		{
			if (mConsoleInputBox->IsFocus())
				mProccessing = true;
		}

		void Console::GetNextInCommandHistory()
		{
			if (!mHistory.size())
				return ;
			mHistoryIndex++;
			if (mHistoryIndex >= (int)mHistory.size())
				mHistoryIndex = mHistory.size() - 1;
			mConsoleInputBox->SetText(mHistory[mHistoryIndex]);
		}

		void Console::GetPreviousInCommandHistory()
		{
			if (!mHistory.size())
				return ;
			mHistoryIndex--;
			if (mHistoryIndex < 0)
				mHistoryIndex = 0;
			mConsoleInputBox->SetText(mHistory[mHistoryIndex]);
		}


	} // namespace Core
	
} // namespace Yuna


