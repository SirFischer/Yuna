#include "MenuState.hpp"

MenuState::MenuState(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	std::cout << "Instantiated the menu state" << std::endl;
	mStateAction = Yuna::Core::eStateControls::EXIT;
}

MenuState::~MenuState()
{
	std::cout << "Destroyed the menu state" << std::endl;
}

void	MenuState::HandleEvents()
{
	mEventHandler.HandleEvent();
}

void	MenuState::Update()
{

}

void	MenuState::Render()
{
	mWindow->Clear();
	mWindow->Render();
}
