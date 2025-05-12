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

		std::shared_ptr<mf::Container>					Console::mConsoleWidget = NULL;
		std::shared_ptr<mf::Text>						Console::mConsoleTextBox = NULL;
		std::shared_ptr<mf::Text>						Console::mConsoleInputBox = NULL;
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
			mConsoleWidget->SetDisabled(true);
			mConsoleWidget->SetIndex(1);
			mConsoleWidget->SetSizePercentage(true, false);
			mConsoleWidget->SetSize(100, 500);
			mConsoleWidget->GetBackground()->SetBackground(sf::Color(57, 57, 57, 200));
			mf::GUI::AddWidget(mConsoleWidget);

			mConsoleTextBox = mf::Text::Create();
			mConsoleTextBox->SetSizePercentage(true, true);
			mConsoleTextBox->SetSize(98, 85);
			mConsoleTextBox->GetText()->LoadFont("assets/fonts/FiraCode-VariableFont_wght.ttf");
			mConsoleTextBox->SetPositionPercentage(true, true);
			mConsoleTextBox->SetPosition(1, 1);
			mConsoleTextBox->GetBackground()->SetBackground(sf::Color(37, 37, 37, 200));
			mConsoleTextBox->GetBackground()->SetOutlineColor(sf::Color(100, 100, 100, 255));
			mConsoleTextBox->GetBackground()->SetOutlineThickness(1);
			mConsoleTextBox->GetText()->SetPos(sf::Vector2f(5, 5));
			mConsoleTextBox->GetText()->SetSize(14);
			mConsoleTextBox->GetText()->SetColor(sf::Color(255, 255, 255, 255));
			mConsoleTextBox->GetScrollBar()->GetBackground()->SetBackground(sf::Color(37, 37, 37, 200));
			mConsoleTextBox->GetScrollBar()->GetButton()->GetBackground()->SetBackground(sf::Color(160, 160, 160, 160));
			mConsoleWidget->AddWidget(mConsoleTextBox);

			mConsoleInputBox = mf::Text::Create();
			mConsoleInputBox->SetSizePercentage(true, false);
			mConsoleInputBox->SetSize(98, 30);
			mConsoleInputBox->GetText()->LoadFont("assets/fonts/FiraCode-VariableFont_wght.ttf");
			mConsoleInputBox->SetPositionPercentage(true, true);
			mConsoleInputBox->SetPosition(1, 90);
			mConsoleInputBox->GetBackground()->SetBackground(sf::Color(37, 37, 37, 200));
			mConsoleInputBox->GetBackground()->SetOutlineColor(sf::Color(100, 100, 100, 255));
			mConsoleInputBox->GetBackground()->SetOutlineThickness(1);
			mConsoleInputBox->GetText()->SetSize(12);
			mConsoleInputBox->GetText()->SetPos(sf::Vector2f(5, 5));
			mConsoleInputBox->GetText()->SetColor(sf::Color(255, 255, 255, 255));
			mConsoleInputBox->EnableEdit();
			mConsoleWidget->AddWidget(mConsoleInputBox);
		}

		void		Console::ToggleConsole()
		{
			mConsoleWidget->SetDisabled(!mConsoleWidget->IsDisabled());
			if (!mConsoleWidget->IsDisabled())
			{
				mHistoryIndex = -1;
				mConsoleInputBox->SetFocus(true);
				mConsoleInputBox->GetText()->SetString("");
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
				mConsoleInputBox->GetText()->SetString("");
				Console::AddString("");
			}
		}

		void		Console::AddString(const std::string &tMessage)
		{
			if (mConsoleTextBox && mConsoleTextBox->GetText())
				mConsoleTextBox->GetText()->AddString(tMessage + '\n');
		}

		void		Console::ClearConsole()
		{
			if (mConsoleTextBox && mConsoleTextBox->GetText())
				mConsoleTextBox->GetText()->SetString("");
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
			mConsoleInputBox->GetText()->SetString(mHistory[mHistoryIndex]);
		}

		void Console::GetPreviousInCommandHistory()
		{
			if (!mHistory.size())
				return ;
			mHistoryIndex--;
			if (mHistoryIndex < 0)
				mHistoryIndex = 0;
			mConsoleInputBox->GetText()->SetString(mHistory[mHistoryIndex]);
		}


	} // namespace Core
	
} // namespace Yuna


